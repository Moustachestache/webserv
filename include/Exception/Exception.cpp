
#include "Exception.hpp"

const char	*UnableToOpenFile::what( void ) const throw()
{
	return ("Unable to open the file.");
}