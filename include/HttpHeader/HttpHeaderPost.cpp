#include "HttpHeader.hpp"

void     HttpHeader::receiveBodyPost(std::string &bodyData)
{
    char    buffer[_bufferSize + 1];
    bzero(buffer, _bufferSize + 1);

    size_t i = _bufferSize;
    int j;
    while (i == _bufferSize)
    {
/*         if (recv(_socket, buffer, _bufferSize, MSG_PEEK) != -1)
        { */
            j = recv(_socket, buffer, _bufferSize, MSG_DONTWAIT);
            if (j <= 0)
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
            _bodyBytesReceived += i;
            appendCStr(buffer, bodyData, i);
            bzero(buffer, _bufferSize + 1);
/*         } */
    }
}

void     HttpHeader::processBodyPost(std::string &bodyData)
{
    std::string     boundary("--" + _boundary);
    std::string     chunk;
    std::string     line;
    size_t          i = bodyData.rfind(boundary + "--");

    if (i == std::string::npos)
        i = bodyData.rfind(boundary);
    while (i != std::string::npos && _error == 0)
    {
        chunk = bodyData.substr(i, bodyData.size() - i);
        bodyData.erase(i, bodyData.size() - i);

        //  retrieve line
        i = chunk.find("Content-Disposition");
        if (i != std::string::npos)
        {
            chunk.erase(0, i);
            line = chunk.substr(0, chunk.find("\r\n\r\n"));
            if (line.find("filename") != std::string::npos)
            {
                processFile(chunk);
            }
            else
                processArg(chunk);
        }
        i = bodyData.rfind(boundary);
    }
}

std::string HttpHeader::getUploadPath( std::vector< Route * > &routes )
{
    std::string res;
    for ( std::vector< Route * >::iterator it = routes.begin(); \
        it != routes.end(); it++)
    {
        if (std::find((*it)->getMethods().begin(), (*it)->getMethods().end(), "POST")\
			!= (*it)->getMethods().end())
        {
            _ptrServer.checkValidRoute((*this), *it, res);
            if (!res.empty())
            {
                if (res.at(res.size() - 1) == '/') /*	path is directory	*/
                {
                    std::string temp = res;
                    for (std::vector< std::string >::iterator itPages = (*it)->getDefaultPages().begin(); \
                        itPages != (*it)->getDefaultPages().end(); itPages++)
                    {
                        temp.append(*itPages);
                        if (!access( temp.c_str() , R_OK))
                        {
                            if ((*it)->getAllowUpload())
                                return ((*it)->getUploadPath());
                        }
                    }
                }
                else /*	path is file	*/
                {
                    if ((*it)->getAllowUpload())
                        return ((*it)->getUploadPath());
                }
            }
        }
        else if (it + 1 == routes.end())
        {
            _error = 405;
            return ("");
        }
    }
    return ("");
}

/* Content-Disposition: form-data; name="picture"; filename="1500x500.jpeg"
Content-Type: image/jpeg */
void    HttpHeader::processFile(std::string &buffer)
{
    int i = buffer.find("name=\"") + 6;
    buffer.erase(0, i);
    i = buffer.find("\"");
    std::string     key = buffer.substr(0, i);
    i = buffer.find("filename=\"") + 10;
    buffer.erase(0, i);
    i = buffer.find("\"");
    std::string     fileName = buffer.substr(0, i);
    i = buffer.find("Content-Type: ") + 14;
    buffer.erase(0, i);
    i = buffer.find("\r\n");
    std::string     mimeType = buffer.substr(0, i);
    i = buffer.find("\r\n\r\n") + 4;
    buffer.erase(0, i);
    std::string     uploadPath = getUploadPath(_ptrServer.getRoute());
    std::ofstream    fileStream;
    if (buffer.size() <= 2)
    {
        _error = 409;
        return ;
    }
    if (uploadPath.empty() || fileName.empty())
    {
        _error = 510;
        return ;
    }
    uploadPath.append(fileName);
    fileStream.open(uploadPath.c_str(), std::ofstream::binary | std::ofstream::trunc);
    if (fileStream.is_open() == false)
    {
        _error = 510;
        return ;
    }
    fileStream.write(buffer.c_str(), buffer.length());
    //fileStream << buffer;
    _postFiles[key] = (fileInfo){fileName, mimeType, uploadPath};
    fileStream.close();
}

void    HttpHeader::processArg(std::string &buffer)
{
    int i = buffer.find("name=\"") + 6;
    //Changement de cookies
    buffer.erase(0, i);
    i = buffer.find("\"");
    std::string     key = buffer.substr(0, i);
    i = buffer.find("\r\n\r\n") + 4;
    buffer.erase(0, i);
    std::string     value = buffer.substr(0, std::string::npos);
    stringSanitize(key);
    stringSanitize(value);
    _post[key] = value;
}

void    HttpHeader::appendCStr(char *src, std::string &dest, size_t j)
{
    for (size_t i = 0; i < j; i++)
    {
        dest.push_back((char)src[i]);
        src[i] = 0;
    }
}