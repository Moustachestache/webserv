# include "HttpHeader.hpp"

HttpHeader::HttpHeader( std::string body ) : _error(0)
{
//  GET /specials/saw-blade.gif HTTP/1.0
//  Host: www.joes-hardware.com
    std::istringstream      iss;

    iss.str(body);
    if (!(iss >> _method))
        _error = 400;
    if (!(iss >> _ressource))
        _error = 400;
    if (!(iss >> _version))
        _error = 400;
    if (_version.compare("HTTP/1.1") && _version.compare("HTTP/1.0") && _error == 0)
        _error = 505;
    //  parse all headers
    std::string buffer;
    std::string index;
    int i = 0;
    while (std::getline(iss, buffer))
    {
        i = buffer.find_first_of(":");
        index = buffer.substr(0, i - 1);
        _args[index] = buffer.substr(i + 1, std::string::npos);
        if (!index.compare("multipart/form-data"))  //not handled yet
            _error = 501;
        else if (!index.compare("application/x-www-form-urlencoded"))
        {
        //    _filePath = savePostFile(iss, _args[index]);
        }
    }
    //  parse all get

    //  parse all post
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


std::map<std::string , std::string> &HttpHeader::getArgs()
{
    return _args;
}