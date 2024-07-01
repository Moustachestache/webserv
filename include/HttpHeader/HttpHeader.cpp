# include "HttpHeader.hpp"

//  set buffer size
const std::size_t HttpHeader::_bufferSize = 4096;

HttpHeader::HttpHeader( HttpHeader &cpy ) : _socket(cpy._socket), _ptrServer(cpy._ptrServer),\
                                            _headerBytesReceived(cpy._headerBytesReceived),\
                                            _bodyBytesReceived(cpy._bodyBytesReceived),\
                                            _error(cpy._error), _method(cpy._method),\
                                            _ressource(cpy._ressource), _version(cpy._version),\
                                            _boundary(cpy._boundary), _args(cpy._args),\
                                            _post(cpy._post), _postFiles(cpy._postFiles),\
                                            _argv(cpy._argv) //jpp
{

}

HttpHeader  &HttpHeader::operator=( HttpHeader &cpy )
{
    if (&cpy != this)
    {
        _socket = cpy._socket;
        _ptrServer = cpy._ptrServer;
        _headerBytesReceived = cpy._headerBytesReceived;
        _bodyBytesReceived = cpy._bodyBytesReceived;
        _error = cpy._error;
        _method = cpy._method;
        _ressource = cpy._ressource;
        _version = cpy._version;
        _boundary = cpy._boundary;
        _args = cpy._args;
        _post = cpy._post;
        _postFiles = cpy._postFiles;
        _argv = cpy._argv;
    }
    return (*this);
}

HttpHeader::HttpHeader( int socket, TcpServer &ptrServer ): 
        _socket(socket), 
        _ptrServer(ptrServer), 
        _headerBytesReceived(0),
        _bodyBytesReceived(0),
        _error(0)
{
    (void) ptrServer;
    char    buffer[_bufferSize + 1];
    bzero(buffer, _bufferSize + 1);

    std::string headerData;
    std::size_t i = _bufferSize;
    int j;
    while (i == _bufferSize && _ptrServer.getServerRunning())
    {
        j = recv(_socket, buffer, _bufferSize, MSG_DONTWAIT);
        if (j < 0)
        {
            if (errno == EAGAIN || errno == EWOULDBLOCK)
            {
                continue ;
            }
            else
            {
                return ;
            }
        }
        i = j;
        _headerBytesReceived += i;
        appendCStr(buffer, headerData, i);
    }
    //  stash leftover body info
    std::string bodyData;
/*     std::cout << "header::" << headerData << std::endl; */
    if (headerData.find("\r\n\r\n") != std::string::npos)
    {
        bodyData = headerData.substr(headerData.find("\r\n\r\n") + 4, std::string::npos);
        headerData.erase(headerData.find("\r\n\r\n"), std::string::npos);
    }
    //  process header Request-Line
    std::istringstream      iss;
    iss.str(headerData);
    if (!(iss >> _method))
        _error = 400;
    else if (!(iss >> _ressource))
        _error = 400;
    else if (!(iss >> _version))
        _error = 400;
    else if (_version.compare("HTTP/1.1") && _version.compare("HTTP/1.0"))
        _error = 505;
    else if (headerData.size() > ptrServer.getMaxHeaderSize())
        _error = 431;
    processHeader(iss);
    if (_ressource.find("?") != std::string::npos)
        processBodyGet();
    if (ft_atoi(_args["Content-Length"]) > static_cast< long int >(ptrServer.getMaxRequestSize()))
        _error = 413;
    else if (!_method.compare("POST") && _error == 0)
    {
		
        _bodyBytesReceived = bodyData.size();
        if (_bodyBytesReceived < static_cast< unsigned long int >(ft_atoi(_args["Content-Length"])))
            receiveBodyPost(bodyData);
        if (_bodyBytesReceived > 0)
            processBodyPost(bodyData);
    }
    buildEnvVector();
 }

void    HttpHeader::processHeader(std::istringstream &iss)
{
    std::size_t i;
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
    //  Process POST header info
    //  checking for input error from client
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
    }
}

void     HttpHeader::processBodyGet( void )
{
    std::size_t i = _ressource.find("?");
    std::size_t j;
    std::string key;
    std::string data;
    std::string buffer(_ressource.substr(i, _ressource.size() - i));
    _ressource.erase(i, std::string::npos);
    for (i = buffer.rfind('&'); i != std::string::npos; i = buffer.rfind('&', i))
    {
        //  load
        key = buffer.substr(i, std::string::npos);
        buffer.erase(i, std::string::npos);
        //  handle
        j = key.find("=");
        if (j == std::string::npos)
        {
            getStringSanitize(key);
            _get[key] =  "";
        }
        else
        {
            data = key.substr(0, j);
            key.erase(0, j);
            getStringSanitize(data);
            getStringSanitize(key);
            _get[data] = key;
        }
    }
    //  if buffer has lengthbuffer;
    if (buffer.size())
    {
        getStringSanitize(buffer);
        _get[buffer] = "";
    }
}

void    HttpHeader::stringSanitize(std::string &str)
{
    while (!str.empty() && str.at(0) && isspace(str.at(0)))
        str.erase(0);
    while (!str.empty() && str.at(str.size() - 1) && isspace(str.at(str.size() - 1)))
        str.erase(str.size() - 1);
}

void    HttpHeader::getStringSanitize(std::string &str)
{
    int begin = 0;
    while (str[begin] && (isspace(str[begin]) || str[begin] == '&' || str[begin] == '?' || str[begin] == '='))
        begin++;
    int end = str.size() - 1;
    while (str[end] && (isspace(str[begin]) || str[begin] == '&' || str[begin] == '?' || str[begin] == '='))
        end--;
    if (begin > end)
        str = "";
    else
        str = str.substr(begin, end - begin + 1);
}

//  char **returnEnv[_POSIX_ARG_MAX][1024];
void    HttpHeader::buildEnvVector( void )
{
    std::string line;
    for (std::map < std::string, std::string >::iterator it = _args.begin(); it != _args.end(); it++ )
	{
        line = "HTTP_" + it->first + "=" + it->second;
        _argv.push_back(line);
	}
    for (std::map < std::string, std::string >::iterator it = _post.begin(); it != _post.end(); it++ )
	{
        line = "POST_" + it->first + "=" + it->second;
        _argv.push_back(line);
	}
    for (std::map < std::string, std::string >::iterator it = _get.begin(); it != _get.end(); it++ )
	{
        line = "GET_" + it->first + "=" + it->second;
        _argv.push_back(line);
	}
    for (std::map < std::string, fileInfo >::iterator it = _postFiles.begin(); it != _postFiles.end(); it++ )
	{
        line = "FILE_" + it->first + "=" + it->second.mimeType + ";" + it->second.fileName + ";" + it->second.filePath;
        _argv.push_back(line);
	}
//  debugance
/*      std::cout << "debug::HttpHeader::buildEnvVector( void ):" << std::endl;
    for (std::size_t i = 0; i < _argv.size(); i++)
	{
        std::cout << "      " << _argv[i] << std::endl;
	}
    std::cout << _ressource << std::endl;
//  hehe */
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

std::vector < std::string >    &HttpHeader::getArgv()
{
    return _argv;
}