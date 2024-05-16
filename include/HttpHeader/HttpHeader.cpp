# include "HttpHeader.hpp"

HttpHeader::HttpHeader( std::string incoming )
{
    (void) incoming;
}

HttpHeader::HttpHeader( int id )    :   _errorcode(id), _protocol("HTTP/1.1 ")
{

}

HttpHeader::~HttpHeader()
{

}

std::string     HttpHeader::buildHeader()
{
    std::string returnStr(_protocol);
    if (_errorcode > 0)
    {
        returnStr.append(" " + ft_itoa(_errorcode));
        returnStr.append(" " + HttpError::initInfo(_errorcode).type);
    }
    else
    {
        //  returnstr is normal no error
    }
    return returnStr;
}
/*
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