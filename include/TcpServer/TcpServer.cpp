#include "TcpServer.hpp"

/* TcpServer::TcpServer() : TcpServer(0, 80) 
{
    _addressLen = (sizeof(_address));
//  default constructor calls TcpServer with default value :
//  ip = 0.0.0.0 and port = 80
//  but really this should never happen lol
} */

TcpServer::TcpServer( std::string &serverStr ) : Server(serverStr), _newSocket(), _addressLen(sizeof(_address))
{

}

void	TcpServer::ServerStart()
{
	_socket = socket(AF_INET, SOCK_STREAM, 0);
	if (_socket < 0)
		throw SocketError();
	//	end default
	_address.sin_family = AF_INET;
	_address.sin_port = ntohs(_port);
		_address.sin_addr.s_addr = inet_addr(_ipStr.c_str());
	//_address.sin_addr.s_addr = ntohl(_ip);
	if (bind(_socket, (sockaddr *)&_address, _addressLen) < 0)
		throw ConnectError();
	std::cout << "Starting server: " << _serverName <<  " at " << _ipStr << " on port " << _port << std::endl;
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

void	TcpServer::checkAllDefaultPages( std::vector< std::string > &pages, std::string &fullPath )
{
	for (std::vector < std::string >::iterator it = pages.begin(); it != pages.end(); it++)
	{
		std::cout << "Fullpath:" << fullPath << std::endl;
		fullPath.append("/");
		fullPath.append(*it);
		std::cout << "to search: " << fullPath << "filename:" << *it << std::endl;
		if (!access( fullPath.c_str() , R_OK))
		{
			std::string	awnser = returnFileStr(fullPath);
			awnser.insert(0,  buildHeader((*it).substr((*it).find_last_of("."), std::string::npos), 200, awnser.size()));
			send(_newSocket, awnser.c_str(), awnser.size(), 0);
			close (_newSocket);
			exit(0);
		}
		fullPath.resize(fullPath.size() - ((*it).size() + 1));
		std::cout << "supposed to be the sameFullpath:" << fullPath << std::endl;
	}
}

void	TcpServer::ifExistSend( Route &route, std::string &filename, bool is_end, HttpHeader &header )
{
	std::cout << filename << std::endl; // debug
	std::string	fullPath = BuildRelativePath(_root, route.getPath(), filename);
	// add check of "../"
	std::cout << "Full path:" << fullPath << std::endl; //debug
	DIR					*openDir = opendir(fullPath.c_str());
	
	if (openDir)
	{
		if (!route.getDefaultPages().empty())
			checkAllDefaultPages(route.getDefaultPages(), fullPath);
		std::cout << "ServerAnswerLs()" << std::endl;
		ServerAnswerLs(header, fullPath);
	}
	else if (!access( fullPath.c_str() , R_OK))
	{
		std::string	awnser = returnFileStr(fullPath);
		awnser.insert(0,  buildHeader(filename.substr(filename.find_last_of("."), std::string::npos), 200, awnser.size()));
		send(_newSocket, awnser.c_str(), awnser.size(), 0);
		close (_newSocket);
		exit(0);
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
			std::string filename = header.getFile();
			if (filename.find(route.getPath()) == std::string::npos)
				return (false);
			filename.erase(filename.find(route.getPath()), route.getPath().size() - 1);
			ifExistSend( route, filename, is_end, header );
			return (false);
		}
		else
		{
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
	unsigned long		sent;
	std::string			output;
	DIR					*openDir = opendir(path.c_str());

	(void) header;
	std::cout << "Path :" << path << std::endl;
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
		output.append("<td><a href=\"./");
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
	close (_newSocket);
	exit(0);
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
	close(_newSocket);
	exit(1);
}

void	TcpServer::ServerListen()
{
	if (listen(_socket, _maxConnections) < 0)
		throw ListenFailed();
	int	bytesReceived = 0;
	while (bytesReceived >= 0 && bytesReceived <= _maxConnections)
	{
		_newSocket = accept(_socket, (sockaddr *)&_address, &_addressLen);
		int pid = fork();
		if (!pid)
		{
			if (_newSocket < 0)
				throw NewSocketError();
			char buffer[_maxHeaderSize + 2];
			std::string		incoming;
			bytesReceived = recv(_newSocket, buffer, _maxHeaderSize + 1, 0);
			incoming.append(buffer);

			HttpHeader		header(buffer);

			if (header.getError() > 0)
				ServerAnswerError(header.getError());
			std::cout << incoming << std::endl;
			if (bytesReceived < 0)
				throw IncomingBytesFailed();
			else if (bytesReceived > _maxHeaderSize)
				ServerAnswerError(413);
			else 
				ServerAnswerGet(header);
			close(_newSocket);
			exit(0);
		}
	}
}

TcpServer::~TcpServer()
{
    //close(_socket);
}