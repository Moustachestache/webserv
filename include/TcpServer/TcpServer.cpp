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
    //	_address.sin_addr.s_addr = inet_addr(_ipStr.c_str());
    _address.sin_addr.s_addr = ntohl(_ip);
    if (bind(_socket, (sockaddr *)&_address, _addressLen) < 0)
        throw ConnectError();
    std::cout << std::endl << "Starting Server at " << _ipStr << " on port " << _port << std::endl;
	ServerListen();
}

void	TcpServer::ServerAnswer(std::string incoming)
{
	unsigned long		sent;
	std::string			output;

	(void) sent;
	(void) incoming;
	(void) output;
//	if (sent != output.size())
//		throw	AnswerFailure();
}

void	TcpServer::ServerAnswerGet(std::string incoming)
{
	unsigned long		sent;
	std::string			output;

	(void) sent;
	(void) incoming;
	(void) output;

//	if (sent != output.size())
//		throw	AnswerFailure();
}

//	build webpage that lists folder
//	struct dirent *readdir(DIR *dirp);
void	TcpServer::ServerAnswerLs(std::string incoming, std::string path)
{
	unsigned long		sent;
	std::string			output;
	DIR					*openDir = opendir(path.c_str());
	if (openDir == NULL)
		ServerAnswerError(500);
	output.append("<!DOCTYPE html><html data-theme=\"dark\"><head><link rel=\"stylesheet\" href=\"https://cdn.jsdelivr.net/npm/@picocss/pico@2/css/pico.min.css\"/><link href=\"https://unpkg.com/boxicons@2.1.4/css/boxicons.min.css\" rel=\"stylesheet\"><title>");
	output.append(_serverName + "/" + path + " folder listing</title></head><body><div class=\"container\">");
	for (dirent	*folderScan = readdir(openDir); openDir != NULL && folderScan != NULL; folderScan = readdir(openDir))
	{
		output.append("<div class=\"grid\" background-color=\"pico-background-slate-900\">");
		if (folderScan->d_type == DT_DIR)
			output.append("<div><i class=\"bx bx-folder\"></i></div>");
		else if (folderScan->d_type == DT_REG)
			output.append("<div><i class=\"bx bxs-file\"></i></div>");
		else if (folderScan->d_type == DT_UNKNOWN)
			output.append("<div><i class=\"bx bx-meh-blank\"></i></div>");
		output.append("<div><a href=\"./");
		output.append(folderScan->d_name);
		output.append("\">");
		output.append(folderScan->d_name);
		output.append("</a></div><div>" + getMimeType(folderScan->d_name) + "</div>");
		output.append("</div>");
	}
	output.append("</div></body>");
	closedir(openDir);

//	if (sent != output.size())
//		throw	AnswerFailure();
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
		//	fork()
		int pid = fork();
		if (!pid)
		{
			//	errcheck
			if (_newSocket < 0)
				throw NewSocketError();
			char buffer[_maxHeaderSize + 2];
			std::string		incoming;
			//	make recv
			bytesReceived = read(_newSocket, buffer, _maxHeaderSize + 1);
			incoming.append(buffer);
			//	parse received http header
			/*while (readed > 0)
			{
				readed = read(_newSocket, buffer, _maxHeaderSize);
				incoming.append(buffer);
			} */
			HttpHeader		header(buffer);
			if (header.getError() > 0)
				ServerAnswerError(header.getError());
			std::cout << incoming << std::endl;
			if (bytesReceived < 0)
				throw IncomingBytesFailed();
			else if (bytesReceived > _maxHeaderSize)
				ServerAnswerError(413);
			else 
				ServerAnswerGet(incoming);
			close(_newSocket);
			exit(0);
		}
	}
}

TcpServer::~TcpServer()
{
    //close(_socket);
}