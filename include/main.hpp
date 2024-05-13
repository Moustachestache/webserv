
#pragma once

/*		C++ LIBRARIES		*/

# include <iostream>
# include <vector>
# include <fstream>
# include <sstream>
# include <exception>
# include <algorithm>
# include <map>

/*		CLASSES		*/

# include "Prog/Prog.hpp"
# include "Exception/Exception.hpp"
# include "Server/Server.hpp"
# include "Route/Route.hpp"
# include "confKeywords.hpp"

/*		STRUCTURE		*/

struct Bracket
{
	size_t	nb;
	size_t	pos;
};

/*		FUNCTIONS		*/

std::string	returnFileStr( std::string fileName );


size_t	getChunkStart( std::istringstream &iss, std::string &fileContent, std::string chunkName );
size_t	getNextBracket( std::string &fileContent, size_t pos);
size_t	getChunkEnd( std::string &fileContent, size_t pos );