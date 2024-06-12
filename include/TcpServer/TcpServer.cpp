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
	addLog("Starting server: " + _serverName + " at " + _ipStr + " on port " + ft_itoa(_port));
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
			addLog( "Server answer: 200" );
			std::string	awnser = returnFileStr(fullPath);
			Generate_Cookie(awnser);
			awnser.insert(0,  buildHeader((*it).substr((*it).find_last_of("."), std::string::npos),\
				200, awnser.size(), getRoute()));
			Generate_Cookie(awnser);
			send(_newSocket, awnser.c_str(), awnser.size(), 0);
			return (true);
		}
		fullPath.resize(fullPath.size() - ((*it).size()));
	}
	return (false);
}

void	TcpServer::ifExistSend( Route &route, std::string &filename, HttpHeader &header, std::string &res )
{
	std::string	fullPath = BuildRelativePath(_root, route.getPath(), filename);
	// add check of "../"
	DIR					*openDir = opendir(fullPath.c_str());

	(void) header;
	if ((!fullPath.empty() && fullPath.at(fullPath.size() - 1) == '/')\
				&& openDir) /* Make sure there is a '/' and the folder is open */
		res = fullPath;
	else if ((!fullPath.empty() && fullPath.at(fullPath.size() - 1) != '/')\
				&& !openDir && !access( fullPath.c_str() , R_OK)) /* make sure there is no '/'
							and make sure no dir got the same name and the file is accessible */
		res = fullPath;
	if (openDir)
		closedir(openDir);
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

	if (openDir == NULL)
	{
		ServerAnswerError(500);
		return ;
	}
	output.append("<!DOCTYPE html><html data-theme=\"dark\"><head><link rel=\"stylesheet\" href=\"https://cdn.jsdelivr.net/npm/@picocss/pico@2/css/pico.min.css\"/><link rel=\"stylesheet\" href=\"https://cdn.jsdelivr.net/npm/@picocss/pico@2/css/pico.colors.min.css\" /><link href=\"https://unpkg.com/boxicons@2.1.4/css/boxicons.min.css\" rel=\"stylesheet\"><title>");
	output.append(_serverName + header.getFile() + " folder listing</title></head><body><div class=\"container\"><h1 class=\"grid\">index of " + header.getFile() + "</h1><table><th></th><th>type</th><th>name</th><th>mime/type</th>");
	for (dirent	*folderScan = readdir(openDir); openDir != NULL && folderScan != NULL; folderScan = readdir(openDir))
	{
		output.append("<tr class=\"pico-background-grey-850\">");
		if (folderScan->d_type == DT_DIR)
			output.append("<td><i class=\"bx bx-folder\"></i></td><td>folder</td>");
		else if (folderScan->d_type == DT_REG)
			output.append("<td><i class=\"bx bxs-file\"></i></td><td>file</td>");
		else if (folderScan->d_type == DT_UNKNOWN)
			output.append("<td><i class=\"bx bx-meh-blank\"></i></td><td>thing</td>");
		output.append("<td><a href=\"./");
		output.append(folderScan->d_name);
		if (folderScan->d_type == DT_DIR)
			output.append("/");
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
	addLog( "Server answer: 200" );
	output.insert(0, buildHeader(".html", 200, output.size(), getRoute()));
	send(_newSocket, output.c_str(), output.size(), 0);
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
					addLog( "Server answer: 200" );

					std::string	awnser = returnFileStr(res);
					awnser.insert(0,  buildHeader(res.substr(res.find_last_of("."), std::string::npos),\
						200, awnser.size(), getRoute()));
					send(_newSocket, awnser.c_str(), awnser.size(), 0);
				}
				return ;
			}
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

	addLog( "Server answer: " + ft_itoa(id) );
	output.insert(0, buildHeader(".html", id, output.size(), getRoute()));
	sent = write(_newSocket, output.c_str(), output.size());
	if (sent != output.size())
		throw	AnswerFailure();
	return ;
}

void	TcpServer::deleteFile( std::string &res )
{
	if (std::remove( res.c_str() ))
	{
		addLog( "File: " + res + " can't be deleted, no such file or directory.");
		ServerAnswerError(204);
	}
	else
	{
		addLog( "File: " + res + " has been deleted.");
		ServerAnswerError(200);
	}
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
/* 		//	for now: execve into py script
		//	name.struct()
		int	pid = fork();
		if (pid == 0)
		{
			char pythonVer[] = "/bin/python3";
			char scriptPath[] = "cgi-bin/upload.py";
			char *array[5] = {pythonVer, scriptPath, const_cast<char *>(header.getFiles()["filename"].fileName.c_str()), const_cast<char *>(header.getFiles()["filename"].mimeType.c_str()), const_cast<char *>(header.getFiles()["filename"].rawData.c_str())};
			execve("pythonVer", array, NULL);
		}
		else
		{
			waitpid(pid, NULL, 0);
		} */
	ServerAnswerError(200);
}

void	TcpServer::ServerListen()
{
	_newSocket = accept(getSocket(), (sockaddr *)&_address, &_addressLen);
	if (_newSocket < 0)
		throw NewSocketError();
	HttpHeader		header(_newSocket, *this);

	addLog( "New incoming connection on server " + _serverName + ": " + header.getMethod() + " " + header.getFile() );
	if (header.getError() > 0)
		ServerAnswerError(header.getError());
	else if (isCgi(getRoute(), header) == true)
		execCgi(header, true_path(getRoute(), header), getRoute() );
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
	addLog("Closing server: " + _serverName + " at " + _ipStr + " on port " + ft_itoa(_port));
	if (_newSocket)
		close(_newSocket);
}