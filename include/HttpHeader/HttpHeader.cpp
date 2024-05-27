# include "HttpHeader.hpp"

HttpHeader::HttpHeader( std::string body ) : _error(0)
{
//  GET /specials/saw-blade.gif HTTP/1.0
//  Host: www.joes-hardware.com
    std::istringstream      ss;

    ss.str(body);
    if (!(ss >> _method))
        _error = 400;
    if (!(ss >> _file))
        _error = 400;
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
    return  _file;
}

std::vector < std::string > &HttpHeader::getArgs()
{
    return  _args;
}