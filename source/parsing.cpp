
#include "../include/main.hpp"

std::string	ft_itoa( int val )
{
	std::stringstream	ss;
	ss << val;
	std::string	res;
	ss >> res;
	return (res);
}

int	ft_atoi( std::string &nb )	/*	if no number found it will return 0	*/
{
	int res = 0;
	std::istringstream	iss(nb);
	iss >> res;
	return (res);
}

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
	Bracket	open = { 0, 0 };
	Bracket close = { 0, 0 };

	pos = getFirstBracket( fileContent, pos);
	if (fileContent.at(pos) == '}' || pos == std::string::npos)
		throw BracketsError();
	open.nb++;
	pos++;
	while (open.nb != close.nb)
	{
		pos = getNextBracket( fileContent, pos );
		if (pos == std::string::npos)
			throw BracketsError();
		if (fileContent.at(pos) == '}')
			close.nb++;
		else if (fileContent.at(pos) == '{')
			open.nb++;
		pos++;
	}
	if (pos == std::string::npos)
		throw BracketsError();
	return (pos - 1);
}

bool	isPathRelative( std::string &path )
{
	if (path.empty())
		return (false);
	if (path.at(0) == '/')
		return (false);
	if (path.find(".") != std::string::npos || path.find("//") != std::string::npos)
		return (false);
	return (true);
}

void	checkValidIp( std::string &ip )
{
	std::istringstream	iss(ip);
	char	dot;
	int		val;
	for (int i = 0; i < 4; ++i)
	{
		if (!(iss >> val))
			throw WrongHeader();
		if (val < 0 || val > 255)
			throw WrongHeader();
		if (i < 3)
		{
			if (!(iss >> dot))
				throw WrongHeader();
			if (dot != '.')
				throw WrongHeader();
		}
	}
}

std::string	BuildRelativePath( std::string first, std::string second, std::string third )
{
	if (first.empty() && second.empty() && third.empty())
		return ("");
	std::string	res = "./";
	res.append(first);
	res.append("/");
	res.append(second);
	res.append("/");
	res.append(third);
	while (res.find("//") != std::string::npos)
		res.replace( res.find("//"), sizeof("//") - 1, "/");
	return (res);
}