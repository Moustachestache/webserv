#include "HttpError.hpp"
#include "../Exception/Exception.hpp"

int HttpError::ErrNumArray[] = { 100, 101, \
                            200, 201, 202, 203, 203, 205, 206, \
                            300, 301, 302, 303, 304, 305, 306, 307, \
                            400, 401, 402, 403, 404, 405, 406, 407, 408, 409, 410, 411, 412, 413, 414, 415, 416, 417, 422,\
                            500, 501, 502, 503, 504, 505, -1};

HttpError::HttpError()
{
    _errorList[100] = (errorinfo){100, "Continue", "Request accepted.", ""};
    _errorList[101] = (errorinfo){101, "Switching Protocols", "Server is willing to comply.", ""};
    _errorList[200] = (errorinfo){200, "Request Successful", "The request has succeeded.", ""};
    _errorList[201] = (errorinfo){201, "Created", "The ressource has been created.", ""};
    _errorList[202] = (errorinfo){202, "Accepted", "The request has been accepted for processing.", ""};
    _errorList[203] = (errorinfo){203, "Non Authoritative Information", "Returned Meta-Information is not definitive", "" };
    _errorList[204] = (errorinfo){204, "No Content", "", ""};
    _errorList[205] = (errorinfo){205, "Reset Content", "", ""};
    _errorList[206] = (errorinfo){206, "Partial Content", "", ""};
    _errorList[300] = (errorinfo){300, "Multiple Choice", "The requested ressource corresponds to multiple representations.", ""};
    _errorList[301] = (errorinfo){301, "Moved Permanently", "The requested ressource has been assigned to a new permanent URI.", ""};
    _errorList[302] = (errorinfo){302, "Found", "The requested ressources exists under a different URI.", ""};
    _errorList[303] = (errorinfo){303, "See Other", " The response to the request can be found under a different URI and SHOULD be retrieved using a GET method on that resource.", ""};
    _errorList[304] = (errorinfo){304, "Not Modified", "The document has not been modified", ""};
    _errorList[305] = (errorinfo){305, "Use Proxy", "Ressource must be accessed through a proxy.", ""};
    _errorList[306] = (errorinfo){306, "legacy", "this code must be implemented but is no longer used.", ""};
    _errorList[307] = (errorinfo){307, "Temporary Redirect", "The requested resource resides temporarily under a different URI.", ""};
    _errorList[400] = (errorinfo){400, "Bad Request", "The request could not be understood by the server due to malformed syntex.", ""};
    _errorList[401] = (errorinfo){401, "Unauthorized", "The request requires user authentication.", ""};
    _errorList[402] = (errorinfo){402, "Payment Required", "oops lol", ""};
    _errorList[403] = (errorinfo){403, "Forbidden", "The server understood the request, but is refusing to fulfill it.", ""};
    _errorList[404] = (errorinfo){404, "Not Found", "The server has not found anything matching the request-URI.", ""};
    _errorList[405] = (errorinfo){405, "Method Not Allowed", "The method specified in the Request-Line is not allowed for the resource identified by the Request-URI.", ""};
    _errorList[406] = (errorinfo){406, "Not Acceptable", "The resource identified by the request is only capable of generating response entities which have content characteristics not acceptable according to the accept headers sent in the request.", ""};
    _errorList[407] = (errorinfo){407, "Proxy Authentification Required", "Authenticate with proxy before continuing.", ""};
    _errorList[408] = (errorinfo){408, "Request Timeout", "The client did not produce a request within the time that the server was prepared to wait.", ""};
    _errorList[409] = (errorinfo){409, "Conflict", "The request could not be completed due to a conflict with the current state of the resource.", ""};
    _errorList[410] = (errorinfo){410, "Gone", "The requested resource is no longer available at the server and no forwarding address is known.", ""};
    _errorList[411] = (errorinfo){411, "Length Required", "The server refuses to accept the request without a defined Content-Length.", ""};
    _errorList[412] = (errorinfo){412, "Precondition Failed", "One or more of the preconditions given to the request header evaluate to false.", ""};
    _errorList[413] = (errorinfo){413, "Request Entity Too Large", "Request entity is larger than REQUEST_SIZE (see config file).", ""};
    _errorList[414] = (errorinfo){414, "Request URI Too Long", "The server is refusing to service the request because the Request-URI is longer than the server is willing to interpret.", ""};
    _errorList[415] = (errorinfo){415, "Unsuported Media Type", "The entity of the request is in a format not supported by the requested method.", ""};
    _errorList[416] = (errorinfo){416, "Requested Range Not Satisfiable", "", ""};
    _errorList[417] = (errorinfo){417, "Expectations Failed", "Header requests field could not be met.", ""};
    _errorList[422] = (errorinfo){422, "Unprocessable Entity", "The demands of the entity are unprocessable ... for some reason?", ""};
    _errorList[500] = (errorinfo){500, "Internal Server Error", "The server encountered an unexpected condition which prevented it from fulfilling the request.", ""};
    _errorList[501] = (errorinfo){501, "Not Implemented", "The server does not support the functionality required to fulfill the request method.", ""};
    _errorList[502] = (errorinfo){502, "Bad Gateway", "Invalid upstream response.", ""};
    _errorList[503] = (errorinfo){503, "Service Unavailable", "The server is currently unable to handle the request due to a temporary overloading or maintenance of the server. Our server hamster possible passed away.", ""};
    _errorList[504] = (errorinfo){504, "Gateway Timeout", "Upstream response was too slow.", ""};
    _errorList[505] = (errorinfo){505, "HTTP Version Not Supported", "The server does not support the requested HTTP protocol version.", ""};
    _errorList[0] = (errorinfo){0, "woopsie", "this should not have happened", ""};
/*    for (int i = 0; ErrNumArray[i] != -1; i++)
    {
        _errorList[ErrNumArray[i]] = initInfo(ErrNumArray[i]);
    }
}*/
}

HttpError::HttpError( HttpError &val ) : _errorList(val._errorList)
{

}

HttpError::~HttpError()
{
/*     for (std::map < int, errorinfo >::iterator itr = _errorList.begin(); itr != _errorList.end(); itr++)
    {
        std::cout << "DEBUG -- " << itr->second.type << "--" << itr->second.file  << std::endl;
    } */
}

HttpError   &HttpError::operator=( HttpError &cpy )
{
    if (&cpy != this)
        _errorList = cpy._errorList;
    return (*this);
}

void    HttpError::addErrorPage(int id, std::string page)
{
    for (size_t i = 0; ErrNumArray[i] != -1; i++)
    {
        if (id == ErrNumArray[i])
        {
            _errorList[id].file = page;
            return ;
        }
    }
    throw WrongHttpErrorNumber();
}

const errorinfo   HttpError::getInfo(int id)
{
    
    for (std::map<int, errorinfo >::iterator it = _errorList.begin(); it != _errorList.end(); it++)
    {
        if (it->second.code == id)
            return (it->second);
    }
    return  (getInfo(0));
}