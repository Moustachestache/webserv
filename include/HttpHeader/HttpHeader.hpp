#pragma once
#include "../main.hpp"
//#include "../Server/Server.hpp"


class Server;
//  note:
//  this structure is contained in _postFiles
//  the map is accessed with the name of the field as key.
//  ie:     _postFiles["picture"]
struct fileInfo {
    //  name of the uploaded file
    std::string fileName;
    //  mime type as told by the browser
    std::string mimeType;
    //  file data
    std::string rawData;
};


class HttpHeader {
    public:
        HttpHeader( int socket, Server &ptrServer );
        ~HttpHeader();
        std::string &getMethod();
        std::string &getFile();
        int &getError();
        void    stringSanitize(std::string &str);
        void    processHeader(std::istringstream &iss, std::string &bodyData);
        int     processBodyPost(std::string &body);
        int     processBodyGet(std::string &body);

        //  map getters
        std::map < std::string, std::string >   &getArgs();
        std::map < std::string, std::string >   &getPost();
        std::map < std::string, fileInfo >   &getFiles();
        std::map < std::string, std::string >   &getGet();

    private:
        int             _socket;
        Server&         _ptrServer;
        static size_t   _bufferSize;
        size_t          _bytesReceived;
        int             _error;
        std::string     _method;
        std::string     _ressource;
        std::string     _version;
        std::string     _boundary;

        //  stores header fields
        std::map < std::string, std::string >   _args;
        //  stores all post info
        std::map < std::string, std::string >   _post;
        //  stores FILES uploaded through post
        std::map < std::string, fileInfo >      _postFiles;
        //  stores potential get data
        std::map < std::string, std::string >   _get;
};