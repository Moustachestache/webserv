# include "HttpHeader.hpp"

HttpHeader::HttpHeader( std::string body )
{
}

HttpHeader::~HttpHeader()
{

}

std::string &HttpHeader::getMethod()
{
    return _method;
}

std::string &HttpHeader::getFile()
{
    return _file;
}

std::vector < std::string > &HttpHeader::getArgs()
{
    return _args;
}

/*std::string     HttpHeader::buildHeader()
{
    std::string returnStr(_protocol);
    HttpError       error;

    returnStr.append(" " + ft_itoa(_errorcode));
    returnStr.append(" " + error.getInfo(_errorcode).type);
    returnStr.append("\n");
    returnStr.append("content-type: " + _contentType + "\n");
    returnStr.append("content-length: " + ft_itoa(_contentSize) + "\n");

    return returnStr;
}
    private:
    //  "HTTP/1.1 200 OK\nContent-Type: text/html\nContent-Length: ";
    //  STATUS LINE DATA (eg:   HTTP/1.1 404 Not Found)
        int             _errorcode;
        std::string     _protocol;
        std::string     _status;
    //  MORE DATA:
        std::string     _connetion;
        std::string     _contentType;
        std::string     _date;
*/