
#include "Prog.hpp"

Prog::Prog( void )
{

}

Prog::~Prog()
{

}

void	Prog::parseFile( char *filePath )
{
	std::ifstream	file;

	file.open(filePath, std::ifstream::in);
	if (!file.is_open())
		throw UnableToOpenFile();
}
