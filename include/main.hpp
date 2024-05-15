
#pragma once

/*		C++ LIBRARIES		*/

# include <iostream>
# include <vector>
# include <fstream>
# include <sstream>
# include <exception>
# include <algorithm>
# include <map>
# include <cstdlib>

/*		C	LIBRAIRIES		*/
# include <sys/socket.h>
# include <arpa/inet.h>
# include <netinet/in.h>
# include <unistd.h>
# include <stdio.h>

/*		CLASSES		*/

# include "Prog/Prog.hpp"
# include "Exception/Exception.hpp"
# include "TcpServer/TcpServer.hpp"
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
}