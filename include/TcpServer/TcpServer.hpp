#pragma once

# include "../main.hpp"
# include "../Server/Server.hpp"
# include "../Socket/Socket.hpp"
# include "../HttpHeader/HttpHeader.hpp"

/*#include <netinet/in.h>

struct sockaddr_in {
    short            sin_family;   // e.g. AF_INET
    unsigned short   sin_port;     // e.g. htons(3490)
    struct in_addr   sin_addr;     // see struct in_addr, below
    char             sin_zero[8];  // zero this if you want to
};

struct in_addr {
    unsigned long s_addr;  // load with inet_aton()
};*/

class   HttpHeader;

class TcpServer : public Server
{
    public:

        //TcpServer();
        TcpServer( std::string &serverStr );
        TcpServer( TcpServer &val );
        ~TcpServer();

        void    checkValidRoute( HttpHeader &header, Route &route, std::string &res );
        void	ifExistSend( Route &route, std::string &filename, HttpHeader &header, std::string &res );
        bool    checkAllDefaultPages( std::vector< std::string > &pages, std::string &fullPath );

        void	ServerListen();
/* 		void	ServerAnswer(std::string incoming); */
        void    ServerAnswerGet( HttpHeader &header );
        void    ServerAnswerDelete( HttpHeader &header );
        void	ServerAnswerError(int id);
        void    ServerAnswerLs(HttpHeader &header, std::string path);
        void	ServerStart();
        int     getSocket( void ) { return _socket.getSocket(); }

    private:

        Socket              _socket;
        char                **_env;
        int                 _newSocket;
        struct sockaddr_in  _address;
        unsigned int        _addressLen;
};