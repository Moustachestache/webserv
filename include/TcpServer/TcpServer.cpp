#include "TcpServer.hpp"

/* TcpServer::TcpServer() : TcpServer(0, 80) 
{
    _addressLen = (sizeof(_address));
//  default constructor calls TcpServer with default value :
//  ip = 0.0.0.0 and port = 80
//  but really this should never happen lol
} */

TcpServer::TcpServer( std::string &serverStr ) :	Server(serverStr), \
													Socket(_ipStr, _port), \
													_newSocket(), \
													_addressLen(sizeof(_address))
{
	std::cout << "Starting server: " << _serverName <<  " at " << _ipStr << " on port " << _port << std::endl;
}

// Copy constructor
TcpServer::TcpServer( TcpServer &val ) :	Server(val), \
											Socket(val), \
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
		fullPath.append("/");
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

/*Uranium*/

void	TcpServer::ifExistSend( Route &route, std::string &filename, bool is_end, HttpHeader &header )
{
	std::string	fullPath = BuildRelativePath(_root, route.getPath(), filename);
	// add check of "../"
	DIR					*openDir = opendir(fullPath.c_str());
	
	if (openDir)
	{
		closedir(openDir);
		if (!route.getDefaultPages().empty())
		{
			if (checkAllDefaultPages(route.getDefaultPages(), fullPath))
				return ;
		}
		ServerAnswerLs(header, fullPath);
	}
	else if (!access( fullPath.c_str() , R_OK) && isCgi(route, filename) == true)
	{

		std::cout <<"C'est bien un CGI TKT bo gosse" << std::endl;
		execCgi(header);
		std::string	awnser = returnFileStr(fullPath);
		awnser.insert(0,  buildHeader(filename.substr(filename.find_last_of("."), std::string::npos), 200, awnser.size()));
		send(_newSocket, awnser.c_str(), awnser.size(), 0);
	}
	else if (!access( fullPath.c_str() , R_OK))
	{
		std::string	awnser = returnFileStr(fullPath);
		awnser.insert(0,  buildHeader(filename.substr(filename.find_last_of("."), std::string::npos), 200, awnser.size()));
		send(_newSocket, awnser.c_str(), awnser.size(), 0);
		return ;
	}
	else if (is_end)
		ServerAnswerError(404);
}

bool	TcpServer::checkValidRoute( HttpHeader &header, Route &route, bool is_end) // 
{
	if (std::find(route.getMethods().begin(), route.getMethods().end(), header.getMethod()) != route.getMethods().end())
	{
		if (route.getRedirection().empty())
		{
			printf("Rubis\n");
			std::string filename = header.getFile();
			if (filename.find(route.getPath()) == std::string::npos)
				return (false);
			filename.erase(filename.find(route.getPath()), route.getPath().size() - 1);
			ifExistSend( route, filename, is_end, header );
			return (false);
		}
		else
		{
			std::cout << " Saphir " << header.getFile() << std::endl;
			std::string filename = header.getFile();
			if (filename.find(route.getRedirection()) == std::string::npos)
				return (false);
			filename.erase(filename.find(route.getRedirection()), route.getRedirection().size() - 1);
			ifExistSend( route, filename, is_end, header );
			return (false);
		}
	}
	else if (is_end)
		ServerAnswerError(405);
	return (true);
}

//	build webpage that lists folder
//	struct dirent *readdir(DIR *dirp);
void	TcpServer::ServerAnswerLs(HttpHeader &header, std::string path)
{
	//unsigned long		sent;
	std::string			output;
	DIR					*openDir = opendir(path.c_str());

	(void) header;
	path.erase(0, _root.size() + 1);
	if (openDir == NULL)
		ServerAnswerError(500);
	output.append("<!DOCTYPE html><html data-theme=\"dark\"><head><link rel=\"stylesheet\" href=\"https://cdn.jsdelivr.net/npm/@picocss/pico@2/css/pico.min.css\"/><link rel=\"stylesheet\" href=\"https://cdn.jsdelivr.net/npm/@picocss/pico@2/css/pico.colors.min.css\" /><link href=\"https://unpkg.com/boxicons@2.1.4/css/boxicons.min.css\" rel=\"stylesheet\"><title>");
	output.append(_serverName + "/" + path + " folder listing</title></head><body><div class=\"container\"><h1 class=\"grid\">index of " + path + "/</h1><table><th></th><th>type</th><th>name</th><th>mime/type</th>");
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

	for (std::vector<Route>::iterator it = route.begin(); it != route.end(); it++)
	{
		if (checkValidRoute(header, *it, (it + 1 == route.end())))
			return ;
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

void	TcpServer::ServerListen()
{
	int	bytesReceived = 0;
	_newSocket = accept(_socket, (sockaddr *)&_address, &_addressLen);
	if (_newSocket < 0)
		throw NewSocketError();
	char buffer[_maxHeaderSize + 2];
	std::string		incoming;
	bytesReceived = recv(_newSocket, buffer, _maxHeaderSize + 1, 0);
	incoming.append(buffer);
	std::cout << "--HEADER_START--" << incoming << "--HEADER_END--" << std::flush; /* debug */
		HttpHeader		header(buffer);
		if (header.getError() > 0)
		ServerAnswerError(header.getError());
	if (bytesReceived < 0)
		throw IncomingBytesFailed();
	else if (bytesReceived > _maxHeaderSize)
		ServerAnswerError(413);
	else 
		ServerAnswerGet(header);
	close(_newSocket);
	_newSocket = 0;
}

TcpServer::~TcpServer()
{
	if (_newSocket)
		close(_newSocket);
}