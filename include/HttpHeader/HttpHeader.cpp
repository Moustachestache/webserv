# include "HttpHeader.hpp"

//  set buffer size
size_t HttpHeader::_bufferSize = 70;

HttpHeader::HttpHeader( int socket, Server &ptrServer ) : _socket(socket), _ptrServer(ptrServer), _bytesReceived(0), _error(0)
{
    (void) ptrServer;
    char    buffer[_bufferSize];

    _bytesReceived = recv(socket, buffer, _bufferSize, 0);
    std::string headerData(buffer);
    while (headerData.find("\r\n\r\n") == std::string::npos /* && bytesReceived > 0 */)
    {
        _bytesReceived = recv(socket, buffer, _bufferSize, 0);
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

    if (headerData.size() > (long unsigned int)ptrServer.getMaxHeaderSize())
        _error = 431;

    processHeader(iss, bodyData);

    if (_ressource.find("?") != std::string::npos)
        processBodyGet(bodyData);
 }

int     HttpHeader::processBodyPost(std::string &body)
{
    std::string buffer;
    std::string key;
    std::string value;
    size_t  j;

    //  helps normalize boundary
    _boundary.insert(0, "--");

    //  delete last iteration of _boundary
    j = body.rfind(_boundary);
    body.erase(j, std::string::npos);

    //  anyway ...
    for (size_t i = body.rfind(_boundary); i != std::string::npos; i = body.rfind(_boundary, i))
    {
        buffer = body.substr(i, std::string::npos);
        body.erase(i, std::string::npos);
        j = buffer.find("filename");
        if (j != std::string::npos)
        {
            j = buffer.find("name=\"") + 6;
            buffer.erase(0, j);
            key = buffer.substr(0, buffer.find("\""));
            stringSanitize(key);
            //
            j = buffer.find("filename=\"") + 10;
            buffer.erase(0, j);
            std::string fileName = buffer.substr(0, buffer.find("\""));
            stringSanitize(fileName);
            //
            j = buffer.find("Content-Type:") + 14;
            buffer.erase(0, j);
            std::string mimeType = buffer.substr(0, buffer.find("\n"));
            stringSanitize(mimeType);
            //  
            j = buffer.find("\r\n\r\n") + 4;
            buffer.erase(0, j);
            _postFiles[key].rawData = buffer.substr(0, buffer.size() - 2);
            _postFiles[key].mimeType = mimeType;
            _postFiles[key].fileName = fileName;
        }
        else if (buffer.size())
        {
            j = buffer.find("name=\"") + 6;
            buffer.erase(0, j);
            j = buffer.find("\"");
            key = buffer.substr(0, j);
            value = buffer.substr(buffer.find("\r\n\r\n"), buffer.rfind("\r\n"));
            stringSanitize(value);
            _post[key] = value;
        }
    }
    return 0;
}


int     HttpHeader::processBodyGet(std::string &body)
{
    (void) body;
    size_t i = _ressource.find("?");
    std::string buffer(_ressource.substr(i, _ressource.size() - i));

    _ressource.erase(i, std::string::npos);
    std::cout << _ressource << " : " << buffer << std::endl;
    return 1;
}

void    HttpHeader::stringSanitize(std::string &str)
{
    int begin = 0;
    while (str[begin] && isspace(str[begin]))
        begin++;
    int end = str.size() - 1;
    while (str[end] && isspace(str[end]))
        end--;
    if (begin > end)
        str = "";
    else
        str = str.substr(begin, end - begin + 1);
}

void    HttpHeader::processHeader(std::istringstream &iss, std::string &bodyData)
{
    size_t i;
    char    buffer[_bufferSize];
    std::string line;
    std::string index;
    std::string strBuffer;
    std::getline(iss, line);
    while (iss.good() && _error == 0)
    {
        i = line.find_first_of(":");
        if (!line.empty() && line.size() != 0 && i != std::string::npos)
        {
            index = line.substr(0, i);
            strBuffer = line.substr(i + 2, line.size() - i);
            stringSanitize(index);
            stringSanitize(strBuffer);
            _args[index] = strBuffer;
        }
        std::getline(iss, line);
    }

    //  if body size too big output error 413
    if ((size_t)std::atol(_args["Content-Size"].c_str()) > _ptrServer.getMaxRequestSize())
        _error = 413;

    //  Process POST body
    if (!_method.compare("POST") && _error == 0)
    {
        //  if "content-length" undefined or empty as a field (0 and above accepted)
        //  return error 411
        if (_args["Content-Length"].size() == 0)
            _error = 411;
            
        //  only working with data/multipart
        //  because fuck you thats why
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
        _bytesReceived = recv(_socket, buffer, _bufferSize, 0);
        i = _bytesReceived;
        while (_bytesReceived == _bufferSize && _bytesReceived < _ptrServer.getMaxRequestSize())
        {
            bodyData.append(buffer);
            bzero(buffer, _bufferSize);
            _bytesReceived = recv(_socket, buffer, _bufferSize, 0);
            i += _bytesReceived;
        }
        bodyData.append(buffer);
        if (i > _ptrServer.getMaxHeaderSize())
        processBodyPost(bodyData);
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

std::map < std::string, std::string >    &HttpHeader::getArgs()
{
    return _args;
}

std::map < std::string, std::string >    &HttpHeader::getPost()
{
    return _post;
}


std::map < std::string, fileInfo >    &HttpHeader::getFiles()
{
    return _postFiles;
}


std::map < std::string, std::string >    &HttpHeader::getGet()
{
    return _get;
}

