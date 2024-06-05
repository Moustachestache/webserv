
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
/* # include <chrono> */


/*		C	LIBRAIRIES		*/

# include <sys/socket.h>
# include <arpa/inet.h>
# include <netinet/in.h>
# include <unistd.h>
# include <stdio.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <dirent.h>
# include <sys/time.h>
# include <sys/wait.h>
# include <sys/select.h>
# include <stdlib.h>
# include <signal.h>
# include <string.h>


/*		CLASSES		*/

# include "Prog/Prog.hpp"
# include "Exception/Exception.hpp"
# include "TcpServer/TcpServer.hpp"
# include "Server/Server.hpp"
# include "Route/Route.hpp"
# include "HttpHeader/HttpHeader.hpp"
# include "confKeywords.hpp"
# include  "Cgi/Cgi.hpp"

/*		TEMPLATES		*/

# include "../source/assignSingleValue.tpp"


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

std::string	getHeaderStr( std::string &chunkStr );
std::string ft_itoa( int val );

std::string     getMimeType(std::string extension);

std::string     buildHeader(std::string extension, int errorcode, int contentSize, std::vector< Route > &allRoutes );


/*          CGI          */
bool            isCgi(Route route, std::string filename);
std::string	    true_path(std::vector<Route> _routes, HttpHeader _header);

std::string    execCgiPost(HttpHeader _header);
std::string    execCgiGet(HttpHeader _header);
std::string    execCgi(HttpHeader _header);
