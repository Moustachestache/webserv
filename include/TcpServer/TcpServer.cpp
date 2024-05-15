#include "TcpServer.hpp"

TcpServer::TcpServer() : TcpServer(0, 80) 
{
    _addressLen = (sizeof(_address));
//  default constructor calls TcpServer with default value :
//  ip = 0.0.0.0 and port = 80
//  but really this should never happen lol
}

TcpServer::TcpServer(unsigned long ip, int port) : _newSocket()
{
    _socket = socket(AF_INET, SOCK_STREAM, 0);
    if (_socket < 0)
        throw SocketError();
    _address.sin_family = AF_INET;
    _address.sin_port = port;
    _address.sin_addr.s_addr = ip;
    if (bind(_socket, (sockaddr *)&_address, sizeof(_address)) < 0)
        throw ConnectError();
    std::cout << "Starting Server at " << _ip << " on port " << _port;
}

TcpServer::~TcpServer()
{
    close(_socket);
}