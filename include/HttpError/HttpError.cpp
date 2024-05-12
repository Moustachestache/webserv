#include "HttpError.hpp"

HttpError::HttpError()
{
    for (int i = 0; HTTP_ERR_NUM[i]; i++)
    {
        _errorList[HTTP_ERR_NUM[i]] = initInfo(HTTP_ERR_NUM[i]);
    }
}

HttpError::HttpError(HttpError &obj)
{
}

HttpError   &HttpError::operator=(HttpError &obj)
{
    return (obj);
}

HttpError::~HttpError()
{
}

errorinfo   HttpError::getInfo(int)
{

}

errorinfo    HttpError::initInfo(int id)
{
    switch (id)
    {
        case 100:
            return ((errorinfo){100, "Continue", "Request accepted.", ""});
        case 101:
            return((errorinfo){101, "Switching Protocols", "Server is willing to comply.", ""});
        case 200:
            return((errorinfo){200, "Request Successful", "The request has succeeded.", ""});
        case 201:
            return((errorinfo){201, "Created", "The ressource has been created.", ""});
        case 202:
            return((errorinfo){202, "Accepted", "The request has been accepted for processing.", ""});
        case 203:
            return((errorinfo){203, "Non Authoritative Information", "Returned Meta-Information is not definitive", "" });
        case 204:
            return((errorinfo){204, "No Content", "", ""});
        case 205:
            return((errorinfo){205, "Reset Content", "", ""});
        case 206:
            return((errorinfo){206, "Partial Content", "", ""});
        case 300:
            return((errorinfo){300, "Multiple Choice", "The requested ressource corresponds to multiple representations.", ""});
        case 301:
            return((errorinfo){301, "Moved Permanently", "The requested ressource has been assigned to a new permanent URI.", ""});
        case 302:
            return((errorinfo){302, "Found", "The requested ressources exists under a different URI.", ""});
        case 303:
            return((errorinfo){303, "See Other", " The response to the request can be found under a different URI and SHOULD be retrieved using a GET method on that resource.", ""});
        case 304:
            return((errorinfo){304, "Not Modified", "The document has not been modified", ""});
        case 305:
            return((errorinfo){305, "Use Proxy", "Ressource must be accessed through a proxy.", ""});
        case 306:
            return((errorinfo){306, "legacy", "this code must be implemented but is no longer used.", ""});
        case 307:
            return((errorinfo){307, "Temporary Redirect", "The requested resource resides temporarily under a different URI.", ""});
        case 400:
            return((errorinfo){400, "Bad Request", "The request could not be understood by the server due to malformed syntex.", ""});
        case 401:
            return((errorinfo){401, "Unauthorized", "The request requires user authentication.", ""});
        case 402:
            return((errorinfo){402, "Payment Required", "oops lol", ""});
        case 403:
            return((errorinfo){403, "Forbidden", "The server understood the request, but is refusing to fulfill it.", ""});
        case 404:
            return((errorinfo){404, "Not Found", "The server has not found anything matching the reauest-URI.", ""});
        case 405:
            return((errorinfo){405, "Method Not Allowed", "The method specified in the Request-Line is not allowed for the resource identified by the Request-URI.", ""});
        case 406:
            return((errorinfo){406, "Not Acceptable", "The resource identified by the request is only capable of generating response entities which have content characteristics not acceptable according to the accept headers sent in the request.", ""});
        case 407:
            return((errorinfo){407, "Proxy Authentification Required", "Authenticate with proxy before continuing.", ""});
        case 408:
            return((errorinfo){408, "Request Timeout", "The client did not produce a request within the time that the server was prepared to wait.", ""});
        case 409:
            return((errorinfo){409, "Conflict", "The request could not be completed due to a conflict with the current state of the resource.", ""});
        case 410:
            return((errorinfo){410, "Gone", "The requested resource is no longer available at the server and no forwarding address is known.", ""});
        case 411:
            return((errorinfo){411, "Length Required", "The server refuses to accept the request without a defined Content-Length.", ""});
        case 412:
            return((errorinfo){412, "Precondition Failed", "One or more of the preconditions given to the request header evaluate to false.", ""});
        case 413:
            return((errorinfo){413, "Request Entity Too Large", "Request entity is larger than REQUEST_SIZE (see config file).", ""});
        case 414:
            return((errorinfo){414, "Request URI Too Long", "The server is refusing to service the request because the Request-URI is longer than the server is willing to interpret.", ""});
        case 415:
            return((errorinfo){415, "Unsuported Media Type", "The entity of the reauest is in a format not supported by the requested method.", ""});
        case 416:
            return((errorinfo){416, "Requested Range Not Satisfiable", "", ""});
        case 417:
            return((errorinfo){417, "Expectations Failed", "Header requests field could not be met.", ""});
        case 500:
            return((errorinfo){500, "Internal Server Error", "The server encountered an unexpected condition which prevented it from fulfilling the request.", ""});
        case 501:
            return((errorinfo){501, "Not Implemented", "The server does not support the functionality required to fulfill the request method.", ""});
        case 502:
            return((errorinfo){502, "Bad Gateway", "Invalid upstream response.", ""});
        case 503:
            return((errorinfo){503, "Service Unavailable", "The server is currently unable to handle the request due to a temporary overloading or maintenance of the server. Our server hamster possible passed away.", ""});
        case 504:
            return((errorinfo){504, "Gateway Timeout", "Upstream response was too slow.", ""});
        case 505:
            return((errorinfo){505, "HTTP Version Not Supported", "The server does not support the requested HTTP protocol version.", ""});
        default:
            return ((errorinfo){0, "woops", "this should not happen", ""});
}