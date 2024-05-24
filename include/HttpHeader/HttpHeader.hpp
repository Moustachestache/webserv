#pragma once
#include "../main.hpp"

class HttpHeader {
    public:
        HttpHeader( std::string body );
        HttpHeader( std::string body, int id );
        ~HttpHeader();
        std::string     buildHeader();
    private:
    //  "HTTP/1.1 200 OK
    //  Content-Type: text/html\nContent-Length: ";
    //  STATUS LINE DATA (eg:   HTTP/1.1 404 Not Found)
        int             _errorcode;
        int             _contentSize;
        std::string     _protocol;
        std::string     _status;
    //  MORE DATA:
        std::string     _connection;
        std::string     _contentType;
        std::string     _date;
};