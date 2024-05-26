#pragma once
#include "../main.hpp"

class HttpHeader {
    public:
        HttpHeader( std::string body );
        ~HttpHeader();
        std::string &getMethod();
        std::string &getFile();
        std::vector < std::string > &getArgs();
    private:
        std::string                     _method;
        std::string                     _file;
        std::vector < std::string >     _args;
};