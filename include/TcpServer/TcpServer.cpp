#include "TcpServer.hpp"

/* TcpServer::TcpServer() : TcpServer(0, 80) 
{
    _addressLen = (sizeof(_address));
//  default constructor calls TcpServer with default value :
//  ip = 0.0.0.0 and port = 80
//  but really this should never happen lol
} */

TcpServer::TcpServer( std::string &serverStr ) :	Server(serverStr), \
													_socket(_ipStr, _port), \
													_newSocket(), \
													_addressLen(sizeof(_address))
{
	std::cout << "Starting server: " << _serverName <<  " at " << _ipStr << " on port " << _port << std::endl;
}

// Copy constructor
TcpServer::TcpServer( TcpServer &val ) :	Server(val), \
											_socket(_ipStr, _port), \
											_newSocket(val._newSocket), \
											_address(val._address), \
											_addressLen(val._addressLen)
{

}

void	TcpServer::ServerStart()
{
	ServerListen();
}

/* void	TcpServer::ServerAnswer(std::string incoming)
{
	unsigned long		sent;
	std::string			output;

    //  build output answer
	(void) incoming;
    //  build header based on answer
	HttpHeader			header(output);
	output.insert(0, "\n\n");
	output.insert(0, header.buildHeader());


	sent = write(_newSocket, output.c_str(), output.size());
	if (sent != output.size())
		throw	AnswerFailure();
} */

bool	TcpServer::checkAllDefaultPages( std::vector< std::string > &pages, std::string &fullPath )
{
	for (std::vector < std::string >::iterator it = pages.begin(); it != pages.end(); it++)
	{
		fullPath.append(*it);
		if (!access( fullPath.c_str() , R_OK))
		{
			std::string	awnser = returnFileStr(fullPath);
			awnser.insert(0,  buildHeader((*it).substr((*it).find_last_of("."), std::string::npos), 200, awnser.size()));
			send(_newSocket, awnser.c_str(), awnser.size(), 0);
			return (true);
		}
		fullPath.resize(fullPath.size() - ((*it).size() + 1));
	}
	return (false);
}

void	TcpServer::ifExistSend( Route &route, std::string &filename, HttpHeader &header, std::string &res )
{
	std::string	fullPath = BuildRelativePath(_root, route.getPath(), filename);
	// add check of "../"
	DIR					*openDir = opendir(fullPath.c_str());
	(void) header;
	
	if (openDir)
	{
		closedir(openDir);
		if (fullPath.at(fullPath.size() - 1) != '/')
			fullPath.append("/");
		res = fullPath;
	}
	else if (!access( fullPath.c_str() , R_OK))
		res = fullPath;
}

void	TcpServer::checkValidRoute( HttpHeader &header, Route &route, std::string &res ) // 
{
	if (route.getRedirection().empty())
	{
		std::string filename = header.getFile();
		if (filename.find(route.getPath()) == std::string::npos)
			return ;
		filename.erase(filename.find(route.getPath()), route.getPath().size() - 1);
		ifExistSend( route, filename, header, res );
	}
	else
	{
		std::string filename = header.getFile();
		if (filename.find(route.getRedirection()) == std::string::npos)
			return ;
		filename.erase(filename.find(route.getRedirection()), route.getRedirection().size() - 1);
		ifExistSend( route, filename, header, res );
	}
}

//	build webpage that lists folder
//	struct dirent *readdir(DIR *dirp);
void	TcpServer::ServerAnswerLs(HttpHeader &header, std::string path)
{
	//unsigned long		sent;
	std::string			output;
	DIR					*openDir = opendir(path.c_str());

	(void) header;
	//path.erase(0, _root.size() + 1); // do not remove + 1 risk to delete one more char
	path.erase(0, _root.size());
	if (!path.empty() && path.at(path.length() - 1) != '/')
		path.append("/");
	if (openDir == NULL)
		ServerAnswerError(500);
	output.append("<!DOCTYPE html><html data-theme=\"dark\"><head><link rel=\"stylesheet\" href=\"https://cdn.jsdelivr.net/npm/@picocss/pico@2/css/pico.min.css\"/><link rel=\"stylesheet\" href=\"https://cdn.jsdelivr.net/npm/@picocss/pico@2/css/pico.colors.min.css\" /><link href=\"https://unpkg.com/boxicons@2.1.4/css/boxicons.min.css\" rel=\"stylesheet\"><title>");
	output.append(_serverName + "/" + path + " folder listing</title></head><body><div class=\"container\"><h1 class=\"grid\">index of " + path + "</h1><table><th></th><th>type</th><th>name</th><th>mime/type</th>");
	for (dirent	*folderScan = readdir(openDir); openDir != NULL && folderScan != NULL; folderScan = readdir(openDir))
	{
		output.append("<tr class=\"pico-background-grey-850\">");
		if (folderScan->d_type == DT_DIR)
			output.append("<td><i class=\"bx bx-folder\"></i></td><td>folder</td>");
		else if (folderScan->d_type == DT_REG)
			output.append("<td><i class=\"bx bxs-file\"></i></td><td>file</td>");
		else if (folderScan->d_type == DT_UNKNOWN)
			output.append("<td><i class=\"bx bx-meh-blank\"></i></td><td>thing</td>");
		output.append("<td><a href=\"" + path);
		output.append(folderScan->d_name);
		output.append("\">");
		output.append(folderScan->d_name);
		output.append("</a></td><td>");
		if (folderScan->d_type == DT_DIR)
			output.append("folder");
		else
			output.append(getMimeType(folderScan->d_name));
		output.append("</td>");
		output.append("</tr>");
	}
	output.append("</table></div></body>");
	closedir(openDir);
	output.insert(0, buildHeader(".html", 200, output.size()));
	send(_newSocket, output.c_str(), output.size(), 0);
	return ;
}

void	TcpServer::ServerAnswerGet( HttpHeader &header )
{
	std::vector< Route >	route = getRoute();
	std::string	res;

	for (std::vector<Route>::iterator it = route.begin(); it != route.end(); it++)
	{
		if (std::find((*it).getMethods().begin(), (*it).getMethods().end(), header.getMethod())\
			!= (*it).getMethods().end())
		{
			checkValidRoute(header, *it, res); //returns the path, still need to check the default pages else lsfiles
			if (!res.empty())
			{
				if (res.at(res.size() - 1) == '/') // path is directory
				{
					if (!checkAllDefaultPages( (*it).getDefaultPages(), res))
						ServerAnswerLs( header, res);
				}
				else // path is file
				{
					std::string	awnser = returnFileStr(res);
					awnser.insert(0,  buildHeader(res.substr(res.find_last_of("."), std::string::npos), 200, awnser.size()));
					send(_newSocket, awnser.c_str(), awnser.size(), 0);
				}
				return ;
			}
			std::cout << res << std::endl;
		}
		else if (it + 1 == route.end())
		{
			ServerAnswerError(405);
			return ;
		}
	}
	ServerAnswerError(404);
}

void	TcpServer::ServerAnswerError(int id)
{
	unsigned long		sent;
	std::string			output(outputErrorPage(id));

	output.insert(0, buildHeader(".html", id, output.size()));
	sent = write(_newSocket, output.c_str(), output.size());
	if (sent != output.size())
		throw	AnswerFailure();
	return ;
}

void	TcpServer::deleteFile( std::string &res )
{
	int	err = 0;
	char **args = new char*[3];
	args[0] = new char[4];
	args[0][0] = '-';
	args[0][0] = 'r';
	args[0][0] = 'f';
	args[0][0] = '\0';
	args[1] = new char[res.size()];
	for (size_t i = 0; i < res.size(); i++)
		args[1][i] = res.at(i);
	args[2] = NULL;
	int pid = fork();
	if (!pid)
		exit (execve("/bin/rm", args ,_env));
	std::cout << "Deleting: " << res << std::endl;
	waitpid(pid, &err, 0);
	err >>= 8;
	if (!err)
		ServerAnswerError(200);
	else
		ServerAnswerError(204);
	std::cout << "Err: " << err << std::endl;
	delete args[0], args[1];
	delete[] args;
}

void	TcpServer::ServerAnswerDelete( HttpHeader &header )
{
	std::vector< Route >	route = getRoute();
	std::string	res;

	for (std::vector<Route>::iterator it = route.begin(); it != route.end(); it++)
	{
		if (std::find((*it).getMethods().begin(), (*it).getMethods().end(), header.getMethod())\
			!= (*it).getMethods().end())
		{
			checkValidRoute(header, *it, res);
			if (!res.empty())
			{
				deleteFile( res);
				return ;
			}
			std::cout << res << std::endl;
		}
		else if (it + 1 == route.end())
		{
			ServerAnswerError(405);
			return ;
		}
	}
	ServerAnswerError(404);
}

void	TcpServer::ServerAnswerPost( HttpHeader &header )
{
		(void) header;
	std::cout << "hello we post" << std::endl;
	
		ServerAnswerError(200);
}

void	TcpServer::ServerListen()
{
	int	bytesReceived = 0;
	_newSocket = accept(getSocket(), (sockaddr *)&_address, &_addressLen);
	if (_newSocket < 0)
		throw NewSocketError();
	HttpHeader		header(_newSocket, *this);
	if (bytesReceived < 0)
		throw IncomingBytesFailed();
	else if (header.getError() > 0)
		ServerAnswerError(header.getError());
	else if (bytesReceived > _maxHeaderSize)
		ServerAnswerError(413);
	else if (!header.getMethod().compare("GET"))
		ServerAnswerGet(header);
	else if (!header.getMethod().compare("DELETE"))
		ServerAnswerDelete(header);
	else if (!header.getMethod().compare("POST"))
		ServerAnswerPost(header);
	else
		ServerAnswerError(405);	// !! add header that lists allowed as answer (bc err 405)
	close(_newSocket);
	_newSocket = 0;
}

TcpServer::~TcpServer()
{
	if (_newSocket)
		close(_newSocket);
}