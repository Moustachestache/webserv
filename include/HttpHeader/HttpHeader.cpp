# include "HttpHeader.hpp"

HttpHeader::HttpHeader( std::string body ) : _error(0)
{
//  GET /specials/saw-blade.gif HTTP/1.0
//  Host: www.joes-hardware.com

//  todo create KVP in a vector ? for get and post
//  key = value (.htm?key=value)
    std::istringstream      iss;

    iss.str(body);
    if (!(iss >> _method))
        _error = 400;
    std::istringstream  stream(_method);
/*     for (std::string buffer; !stream.eof(); stream.getline(buffer, '&'))
    {
        std::cout << "HttpHeader debug: - " << buffer << std::endl;
    } */
    if (!(iss >> _file))
        _error = 400;
    if (!(iss >> _version))
        _error = 400;
    if (_version.compare("HTTP/1.1") && _version.compare("HTTP/1.0"))
        _error = 505;   //  HTTP version not supported - we only work with 1.1 and 1.0
    //  do post if post
    //  to fetch if need
    /* for (std::string    buffer; !iss.eof(); std::getline(iss, buffer))
    {
        std::cout << "HttpHeader debug: - " << buffer << std::endl;
    } */
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