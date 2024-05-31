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

class TcpServer : public Server, public Socket
{
    public:

        //TcpServer();
        TcpServer( std::string &serverStr );
        TcpServer( TcpServer &val );
        ~TcpServer();

        bool    checkValidRoute( HttpHeader &header, Route &route, bool is_end);
        void	ifExistSend( Route &route, std::string &filename, bool is_end, HttpHeader &header );
        bool    checkAllDefaultPages( std::vector< std::string > &pages, std::string &fullPath );

        void	ServerListen();
/* 		void	ServerAnswer(std::string incoming); */
        void    ServerAnswerGet( HttpHeader &header );
        void	ServerAnswerError(int id);
        void    ServerAnswerLs(HttpHeader &header, std::string path);
        void	ServerStart();

        int     getMaxHeaderSize();

    private:

        int                 _newSocket;
        struct sockaddr_in  _address;
        unsigned int        _addressLen;
};