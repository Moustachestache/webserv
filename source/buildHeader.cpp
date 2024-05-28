#include "../include/main.hpp"

std::string     buildHeader(std::string extension, int errorcode, int contentSize)
{
    HttpError   error;
    std::string returnStr("HTTP/1.1 ");

    std::cout << extension << "\n" << getMimeType(extension) << "\n" << std::endl;
    returnStr.append(" " + ft_itoa(errorcode));
    returnStr.append(" " + error.getInfo(errorcode).type);
    returnStr.append("\r\n");
    returnStr.append("content-type: " + getMimeType(extension) + "\r\n");
    returnStr.append("content-length: " + ft_itoa(contentSize) + "\r\n");
    returnStr.append("connection: close\r\n");
    returnStr.append("\n");
//  debug
//    std::cout << "[DEBUG] return HTTP HEADER:" << returnStr << std::endl;
    return returnStr;
}