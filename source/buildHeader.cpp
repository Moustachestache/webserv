#include "../include/main.hpp"

std::string     buildHeader(std::string extension, int errorcode, int contentSize)
{
    HttpError   error;
    std::string returnStr("HTTP/1.1 ");

    returnStr.append(" " + ft_itoa(errorcode));
    returnStr.append(" " + error.getInfo(errorcode).type);
    returnStr.append("\r\n");
    returnStr.append("content-type: " + getMimeType(extension) + "\r\n");
    returnStr.append("content-length: " + ft_itoa(contentSize) + "\r\n");
    //  brother eww. ew brother.
    if (errorcode == 413)
        returnStr.append("Allow: POST DELETE GET\r\n");
    returnStr.append("connection: keep-alive\r\n");
    returnStr.append("\n");
    return returnStr;
}