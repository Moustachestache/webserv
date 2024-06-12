#include "Cookies.hpp"

void    Generate_Cookie(HttpHeader& _header)
{
    std::string	awnser = returnFileStr(fullPath);
    std::cout << "Obiscienne" << std::endl << awnser << std::endl;
	awnser.insert(0,  buildHeader((*it).substr((*it).find_last_of("."), std::string::npos),\
		200, awnser.size(), getRoute()));
    std::cout << "Diamant" << std::endl << awnser << std::endl;
}