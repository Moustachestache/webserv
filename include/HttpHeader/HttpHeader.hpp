#pragma once
#include "../main.hpp"

class HttpHeader {
    public:
        HttpHeader( std::string body );
        ~HttpHeader();
        std::string &getMethod();
        std::string &getFile();
        int &getError();
        std::map<std::string , std::string> &getArgs();
    private:
        int             _error;
        std::string     _method;
        std::string     _ressource;
        //  path = cgi-bin/file-id.temp
        std::string     _filePath;
        std::string     _version;
        std::map < std::string, std::string >    _args;
};