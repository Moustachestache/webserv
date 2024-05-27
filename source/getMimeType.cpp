#include "../include/main.hpp"

struct mimeType
{
    std::string                     type;
    std::string                     extension;
};

//    (mimeType){"", ""},
static  mimeType    mimetable[] = {
        (mimeType){"image/jpeg", ".jpg"},
        (mimeType){"image/jpeg", ".jpeg"},
        (mimeType){"image/png", ".png"},
        (mimeType){"image/gif", ".gif"},

        (mimeType){"text/html", ",htm"},
        (mimeType){"text/html", ".html"},

        (mimeType){"text/css", ".css"},

        (mimeType){"text/plain", ".c"},
        (mimeType){"text/plain", ".cpp"},
        (mimeType){"", ""}
    };


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