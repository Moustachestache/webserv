
#pragma once

# include "../include/Exception/Exception.hpp"

template < typename V >
void	assignSingleValue( std::istringstream &iss, V &to_assign )
{
	std::string	sep;
	V word;
	if (!(iss >> sep))
		throw WrongVariableAssignment();
	else if (sep.compare("="))
		throw WrongVariableAssignment();
	else if (!(iss >> word))
		throw WrongVariableAssignment();
	to_assign = word;
	if ((iss >> sep))
		throw WrongVariableAssignment();
}