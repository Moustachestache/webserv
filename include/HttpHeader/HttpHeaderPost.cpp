#include "HttpHeader.hpp"

void     HttpHeader::receiveBodyPost(std::string &bodyData)
{
    char    buffer[_bufferSize + 1];
    bzero(buffer, _bufferSize + 1);

    size_t i = _bufferSize;
    while (i == _bufferSize)
    {
        i = recv(_socket, buffer, _bufferSize, 0);
        _bodyBytesReceived += i;
        appendCStr(buffer, bodyData, i);
    }
}

void     HttpHeader::processBodyPost(std::string &bodyData)
{
    std::string     boundary("--" + _boundary);
    std::string     chunk;
    std::string     line;

    size_t          i = bodyData.rfind(boundary + "--");
    while (i != std::string::npos && _error == 0)
    {
        chunk = bodyData.substr(i, std::string::npos);
        bodyData.erase(i, std::string::npos);

        //  retrieve line
        i = chunk.find("Content-Disposition");
        if (i != std::string::npos)
        {
            chunk.erase(0, i);
            line = chunk.substr(0, chunk.find("\r\n"));
            if (line.find("filename") != std::string::npos)
                processFile(chunk);
            else
                processArg(chunk);
        }
        i = bodyData.rfind(boundary);
    }
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
//  hardcoded path
//  if we push and we can read this we fucked up!
//  change to dynamic,. gregou stp
    std::string     path = "cgi-bin/upload" + fileName;
    std::ofstream    fileStream;
    fileStream.open(path.c_str(), std::ofstream::binary);
    if (fileStream.is_open() == false)
        _error = 500;
    fileStream << buffer;
    _postFiles[key] = (fileInfo){fileName, mimeType, path};
    fileStream.close();
}

void    HttpHeader::processArg(std::string &buffer)
{
    int i = buffer.find("name=\"") + 6;
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