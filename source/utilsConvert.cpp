
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

unsigned int	strIpToUint( std::string &ip )
{
	unsigned int	res = 0;
	unsigned int	temp;
	char			sep;

	std::istringstream	iss(ip);
	for (int i = 0; i < 4; i++)
	{
		temp = 0;
		iss >> temp;
		res += temp;
		res <<= 8;
		iss >> sep;
	}
	return (res);
}

std::string	BuildRelativePath( std::string first, std::string second, std::string third )
{
	if (first.empty() && second.empty() && third.empty())
		return ("");
	std::string	res = ""; // removed the ./ cause useless
	res.append(first);
	res.append("/");
	res.append(second);
	res.append("/");
	res.append(third);
	while (res.find("//") != std::string::npos)
		res.replace( res.find("//"), sizeof("//") - 1, "/");
	return (res);
}