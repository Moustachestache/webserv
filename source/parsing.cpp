
#include "../include/main.hpp"

std::string ft_itoa( int val )
{
    std::stringstream   ss;
    ss << val;
    std::string res;
    ss >> res;
    return (res);
}

size_t	getChunkStart( std::istringstream &iss, std::string &fileContent, std::string chunkName )
{
	std::string	word;

	if (!(iss >> word))
		return (std::string::npos);
	size_t	pos = word.find(chunkName);
	if (pos == std::string::npos)
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
	if (chunkName.at(chunkName.size() - 1) == '{')
		return (fileContent.find('{', pos));
	else if (chunkName.at(chunkName.size() - 1) == ']')
	{
		if (iss >> chunkName)
		{
			if (chunkName.at(0) == '{')
				return (fileContent.find('{', pos));
		}
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
	return (pos);
}

