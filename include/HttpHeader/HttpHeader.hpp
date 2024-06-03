#pragma once
#include "../main.hpp"

//  key value pair structure
//  store key amnd value of GET / POST method variables
struct kvp {
    std::string key;
    std::string value;
};

class HttpHeader {
    public:
        HttpHeader( int socket, Server &ptrServer );
        ~HttpHeader();
        std::string &getMethod();
        std::string &getFile();
        int &getError();
        std::vector < std::string > &getArgs();
        void    stringSanitize(std::string &str);
        int     processBodyPost(std::string &body);
        int     processBodyGet(std::string &body);

    //  interactions with POST or GET data
        std::string &getMethodValue(std::string key);
        kvp &getMethodKvp(std::string key);

    private:
        static int      _bufferSize;
        int             _error;
        std::string     _method;
        std::string     _ressource;
        //  path = cgi-bin/file-id.temp
        std::string     _filePath;
        std::string     _version;
        std::string     _boundary;
        kvp             *_data;

        std::map < std::string, std::string >    _args;
};