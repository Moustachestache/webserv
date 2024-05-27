#pragma once

# include "../main.hpp"
# include "../Server/Server.hpp"

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

class TcpServer : public Server
{
    public:
        //TcpServer();
        TcpServer( std::string &serverStr );
        ~TcpServer();

        void	ServerListen();
		void	ServerAnswer(std::string incoming);
        void    ServerAnswerGet(std::string incoming);
        void	ServerAnswerError(int id);
        void    ServerAnswerLs(std::string incoming, std::string path);
        void	ServerStart();
    private:
        int                 _socket;
        int                 _newSocket;
        struct sockaddr_in  _address;
        unsigned int        _addressLen;
};