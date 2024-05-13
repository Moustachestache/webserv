
#include "Exception.hpp"

const char	*UnableToOpenFile::what( void ) const throw()
{
	return ("Error: unable to open the file.");
}

const char	*NoServerFound::what( void ) const throw()
{
	return ("Error: no server found in the config.");
}

const char	*WrongWord::what( void ) const throw()
{
	return ("");
}

const char	*BracketsError::what( void ) const throw()
{
	return ("Error: while parsing the brackets.");
}