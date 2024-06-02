# include "HttpHeader.hpp"

//  set buffer size
/* int HttpHeader::_bufferSize = 69; */
int HttpHeader::_bufferSize = 70;

HttpHeader::HttpHeader( int socket, Server &ptrServer ) : _error(0)
{
    (void) ptrServer;
    char    buffer[_bufferSize];

    //  read header until body
    int bytesReceived = recv(socket, buffer, _bufferSize, 0);
    std::string headerData(buffer);
    while (headerData.find("\r\n\r\n") == std::string::npos /* && bytesReceived > 0 */)
    {
        bytesReceived = recv(socket, buffer, _bufferSize, 0);
        headerData.append(buffer);
        bzero(buffer, _bufferSize);
    }
    //  stash leftover body info
    std::string bodyData(headerData.substr(headerData.find("\r\n\r\n")), headerData.size() - headerData.find("\r\n\r\n"));

    //  process header Request-Line
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

    //  https://developer.mozilla.org/en-US/docs/Web/HTTP/Status/431
    //  huh
    if (headerData.size() > (long unsigned int)ptrServer.getMaxHeaderSize())
        _error = 431;

    //  process Header Fields
    size_t i;
    std::string line;
    std::string index;
    std::string strBuffer;
    std::getline(iss, line);
    while (iss.good() && _error == 0)
    {
        // rm this sanitize?
        stringSanitize(line);
        i = line.find_first_of(":");
        if (!line.empty() && line.size() != 0 && i != std::string::npos)
        {
            index = line.substr(0, i);
            strBuffer = line.substr(i + 2, line.size() - i);
            stringSanitize(index);
            stringSanitize(strBuffer);
            _args[index] = strBuffer;
            std::cout << "index     :" << index << std::endl;
            std::cout << "buffer    :" << strBuffer << std::endl;
            std::cout << "mapdata   :" << _args[index] << std::endl;
        }
        std::getline(iss, line);
    }

    //  if body size too big output error 413
    if (std::atoi(_args["Content-Size"].c_str()) > ptrServer.getMaxRequestSize())
        _error = 413;

    //  Process POST body
    if (!_method.compare("POST") && _error == 0)
    {
        //  if "content-length" undefined or empty as a field (0 and above accepted)
        //  return error 411
        if (_args["Content-Length"].size() == 0)
            _error = 411;
        //  only working with data/multipart
        else if (_args["Content-Type"].find("multipart/form-data") == std::string::npos)
            _error = 501;
        else    //retrieve boundary
        {
            i = 0;
            i = _args["Content-Type"].find_last_of("=");
            if (i == std::string::npos)
                _error = 400;
            else
                _boundary = _args["Content-Type"].substr(i + 1, _args["Content-Type"].size());
        }
        bytesReceived = recv(socket, buffer, _bufferSize, 0);
        i = bytesReceived;
        while (bytesReceived == _bufferSize && bytesReceived < ptrServer.getMaxRequestSize())
        {
            bodyData.append(buffer);
            bzero(buffer, _bufferSize);
            bytesReceived = recv(socket, buffer, _bufferSize, 0);
            i += bytesReceived;
        }
        if (i < (size_t)ptrServer.getMaxRequestSize())
            processBodyPost(bodyData, headerData);
        std::cout << bodyData << std::endl;
    }
    else if (!_method.compare("GET") && _error == 0)
    {
        processBodyGet(bodyData, headerData);
    }
    //  process boundary 
    //  process body if need (get or post and content length)

    //  must process every single kvp
    //  and file too!!
    std::cout << "debug dump: " << _method << _ressource << _boundary << std::endl;
}

int     HttpHeader::processBodyPost(std::string &body, std::string &header)
{
    std::cout << "processbody" << std::endl;
    (void) header;
    std::string index;
    std::string value;
    size_t i = body.find(_boundary);
    for (std::string buffer; i != std::string::npos; i = body.find(_boundary, i))
    {
        buffer = body.substr(i, buffer.find(_boundary, i + 1));
        std::cout << "aaaa!!!" << buffer << "aaaaaaaaaaaaahhhh!!" << std::endl;
    }
    return 0;
}


int     HttpHeader::processBodyGet(std::string &body, std::string &header)
{
    (void) body;
    (void) header;
    return 1;
}

void    HttpHeader::stringSanitize(std::string &str)
{
    int begin = 0;
    while (str[begin] && isspace(str[begin]))
        begin++;
    int end = str.size();
    while (str[end] && isspace(str[end]))
        end--;
    if (begin >= end)
        str = "";
    else
        str = str.substr(begin, end);
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