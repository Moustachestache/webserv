
#include "../include/main.hpp"

std::string	getHeaderStr( std::string &chunkStr ) /*	get chunk header returns it as a std::string,
													and delete it in the base str		*/
{
	size_t	startPos = chunkStr.find("[");
	size_t	endPos = chunkStr.find("]");
	std::string res = chunkStr.substr(startPos + 1, endPos - startPos - 1);
	startPos = chunkStr.find("{");
	if (startPos == std::string::npos)
		throw WrongHeader();
	chunkStr.erase(0, startPos + 1);
	return (res);
}

size_t	getChunkStart( std::istringstream &iss, std::string &fileContent, std::string chunkName )
{
	std::string	word;

	if (!(iss >> word))
		return (std::string::npos);
	size_t	pos = word.find(chunkName);
	if (pos != 0)
		return (std::string::npos);
	return (fileContent.find(word));
}

size_t	getNextBracket( std::string &fileContent, size_t pos)
{
	size_t	openPos = fileContent.find('{', pos);
	size_t	closePos = fileContent.find('}', pos);
	if (closePos < openPos)
		return (closePos);
	return (openPos);
}

size_t	getFirstBracket( std::string &fileContent, size_t pos )
{
	std::istringstream	iss(fileContent);
	std::string	chunkName;
	iss >> chunkName;
	if (chunkName.at(chunkName.size() - 1) == '{')/*	case: CHUNK_NAME[var]{
															VAR=VAR
															}	*/
		return (fileContent.find('{', pos));
	else if (chunkName.at(chunkName.size() - 1) == ']') /*	case: CHUNK_NAME[var]
																	{VAR=VAR
																	}	*/
	{
		if (iss >> chunkName)
		{
			if (chunkName.at(0) == '{')
				return (fileContent.find('{', pos));
		}
	}
	size_t	res = chunkName.find('{', pos);
	if (res != std::string::npos) /*	case: CHUNK_NAME[var]{VAR=VAR
																	}	*/
	{
		if (chunkName.at(res - 1) == ']')
			return (res + pos);
	}
	throw BracketsError();
}

size_t	getChunkEnd( std::string &fileContent, size_t pos )
{
	int	open = 0;
	int	close = 0;

	pos = getFirstBracket( fileContent, pos);
	if (fileContent.at(pos) == '}' || pos == std::string::npos)
		throw BracketsError();
	open++;
	pos++;
	while (open != close)
	{
		pos = getNextBracket( fileContent, pos );
		if (pos == std::string::npos)
			throw BracketsError();
		if (fileContent.at(pos) == '}')
			close++;
		else if (fileContent.at(pos) == '{')
			open++;
		pos++;
	}
	if (pos == std::string::npos)
		throw BracketsError();
	return (pos - 1);
}