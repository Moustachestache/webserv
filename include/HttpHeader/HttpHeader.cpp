# include "HttpHeader.hpp"

//  set buffer size
int HttpHeader::_bufferSize = 512;

HttpHeader::HttpHeader( int socket, Server &ptrServer ) : _error(0)
{
    (void) ptrServer;
    std::string headerData;
    char    buffer[_bufferSize + 1];
    int bytesReceived = read(socket, buffer, 512);

    //  read header untuil body
    while (headerData.find("\r\n\r\n") == std::string::npos)
    {
        std::cout << buffer << std::endl;
        bytesReceived = read(socket, buffer, 512);
        headerData.append(buffer);
    }
    //  stash leftover body info
    std::string bodyData(headerData.substr(headerData.find("\r\n\r\n")), std::string::npos);
    headerData.erase(headerData.find("\r\n\r\n"), std::string::npos);
    while (bodyData.find("\r\n\r\n") == std::string::npos)
    {
        bytesReceived = read(socket, buffer, 512);
        bodyData.append(buffer);
    }

    std::cout << "header:" << std::endl << headerData << std::endl;
    std::cout << "body:" << std::endl << bodyData << std::endl;

    std::istringstream      iss;
    iss.str(headerData);
    if (!(iss >> _method))
        _error = 400;
    if (!(iss >> _ressource))
        _error = 400;
    if (!(iss >> _version))
        _error = 400;
    if (_version.compare("HTTP/1.1") && _version.compare("HTTP/1.0") && _error == 0)
        _error = 505;

    std::string line;
    std::string index;
    for (int i = 0; !iss.eof() && _error == 0; std::getline(iss, line))
    {
        i = line.find_first_of(":");
        index = line.substr(0, i - 1);
        _args[index] = line.substr(i + 1, std::string::npos);
        if (!index.compare("multipart/form-data"))  //not handled yet
            std::cout << "lol" << std::endl;
        else if (!index.compare("application/x-www-form-urlencoded"))
        {
            _error = 501;
        }
    }
}

HttpHeader::~HttpHeader()
{

}

std::string &HttpHeader::getMethod()
{
    return  _method;
}

int &HttpHeader::getError()
{
    return  _error;
}

std::string &HttpHeader::getFile()
{
    return  _ressource;
}