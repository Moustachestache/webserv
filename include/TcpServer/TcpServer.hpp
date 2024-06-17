#pragma once

# include "../main.hpp"
# include "../Server/Server.hpp"
# include "../Socket/Socket.hpp"
# include "../HttpHeader/HttpHeader.hpp"
# include "../Cgi/Cgi.hpp"
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

        /*      CONSTRUCTOR/DESTRUCTOR      */

        //TcpServer();
        TcpServer( std::string &serverStr );
        TcpServer( TcpServer &val );
        ~TcpServer();

        /*      OPERATOR OVERLOADING        */

        TcpServer   &operator=( TcpServer &cpy );

        /*      PARSING     */

        void    checkValidRoute( HttpHeader &header, Route &route, std::string &res );
        void	ifExistSend( Route &route, std::string &filename, HttpHeader &header, std::string &res );
        bool    checkAllDefaultPages( std::vector< std::string > &pages, std::string &fullPath );

        /*      SERVER LOGIC        */
        /**/void	ServerListen();
        /**/void    ServerAnswerPost( HttpHeader &header );
        /**/void	ServerAnswerError(int id);
            /*      TcpServerGet.cpp        */
            /**/void    ServerAnswerGet( HttpHeader &header );
            /**/void    ServerAnswerLs(HttpHeader &header, std::string path);
            /*      TcpServerDelete.cpp     */
            /**/void    ServerAnswerDelete( HttpHeader &header );
            /**/void    deleteFile( std::string &res );

        /*      GETTER      */

        int     getSocket( void );

        /*      CGI     */

        std::string	    true_path(std::vector<Route> _routes, HttpHeader _header);
        bool            isCgi(std::vector<Route> route, HttpHeader &_header);
        void            execCgi(HttpHeader _header, std::string true_path, std::vector<Route> routes);
        std::string     execCgiGet(HttpHeader _header, std::string true_path, std::string _path);
        std::string     cgiPath(std::vector<Route> routes, HttpHeader _header);

    private:

        Socket              _socket;
        int                 _newSocket;
        struct sockaddr_in  _address;
        unsigned int        _addressLen;
};