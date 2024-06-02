# include "HttpHeader.hpp"

//  set buffer size
int HttpHeader::_bufferSize = 69;

HttpHeader::HttpHeader( int socket, Server &ptrServer ) : _error(0)
{
    (void) ptrServer;
    char    buffer[_bufferSize + 1];

    //  read header until body
    int bytesReceived = recv(socket, buffer, _bufferSize, 0);
    std::string headerData(buffer);
    while (headerData.find("\r\n\r\n") == std::string::npos /* && bytesReceived > 0 */)
    {
        bytesReceived = recv(socket, buffer, _bufferSize, 0);
        headerData.append(buffer);
    }
    //  stash leftover body info
    //  please change or kill me
    std::string bodyData(headerData.substr(headerData.find("\r\n\r\n")), headerData.size() - headerData.find("\r\n\r\n"));

    //  process header 1st phrase
    //  note:
    //  this is only the header
    //  -> possible body info left to be recv'd
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
    //  stash each header into the map
    unsigned int i;
    std::string line;
    std::string index;
    std::string strBuffer;
    std::getline(iss, line);
    while (iss.good() && _error == 0)
    {
        stringSanitize(line);
        i = line.find_first_of(":");
        if (!line.empty() && line.size() != 0 && i != std::string::npos)
        {
            index = line.substr(0, i);
            strBuffer = line.substr(i + 2, line.size() - i);
            stringSanitize(index);
            stringSanitize(strBuffer);
            _args[index] = strBuffer;
            std::cout << "index :" << index << std::endl;
            std::cout << "data  :" << strBuffer << std::endl;
        }
        std::getline(iss, line);
    }
    //  if "content-length" undefined or empty as a fiel (0 and above accepted)
    //  return error 411
    if (_args["Content-Length"].size == "")
        _error = 411;

    //  if body size too big output error 413
    if (std::atoi(_args["Content-Size"].c_str) > ptrServer->getMaxRequestSize())
        _error = 413;
    //  process body if need (get or post and content length)

    //  must process every single kvp
    //  and file too!!
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