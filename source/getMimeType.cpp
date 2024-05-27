#include "../include/main.hpp"

struct mimeType
{
    std::string                     type;
    std::string                     extension;
};

//    (mimeType){"", ""}, No without the "(mimeType)" it's working lol c con :)
static  mimeType    mimetable[] = {
        {"image/jpeg", ".jpg"},
        {"image/jpeg", ".jpeg"},
        {"image/png", ".png"},
        {"image/gif", ".gif"},
        {"text/html", ".htm"}, // lol ,htm ce koi 7 extention
        {"text/html", ".html"},
        {"text/css", ".css"},
        {"text/plain", ".c"},
        {"text/plain", ".cpp"},
        {"", ""} };


std::string     getMimeType(std::string extension)
{
    //  must parse incoming
    std::string     dotExt(extension.substr(extension.find_last_of("."), std::string::npos));
    for (int i = 0; mimetable[i].type.size() > 0; i++)
    {
        if (!extension.compare(mimetable[i].extension))
            return mimetable[i].type;
    }

    //  massive security breach LOL
    return "text/plain";
}