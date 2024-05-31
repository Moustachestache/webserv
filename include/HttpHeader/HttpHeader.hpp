#pragma once
#include "../main.hpp"

class HttpHeader {
    public:
        HttpHeader( int socket, Server &ptrServer );
        ~HttpHeader();
        std::string &getMethod();
        std::string &getFile();
        int &getError();
        std::vector < std::string > &getArgs();
    private:
        static int      _bufferSize;
        int             _error;
        std::string     _method;
        std::string     _ressource;
        //  path = cgi-bin/file-id.temp
        std::string     _filePath;
        std::string     _version;
        std::map < std::string, std::string >    _args;
};