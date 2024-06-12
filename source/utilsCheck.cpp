
#include "../include/main.hpp"

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
