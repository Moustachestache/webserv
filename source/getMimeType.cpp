#include "../include/main.hpp"

struct mimeType
{
    std::string                     type;
    std::string                     extension;
};

//  returns clean extension.
static std::string  extensionSanitize(std::string &extension)
{
    size_t  dotPos = extension.find_last_of(".");
    std::string sanitized;

    if (dotPos != std::string::npos) //found a dot then we change
        sanitized = extension.substr(extension.find_last_of("."), std::string::npos);
    return sanitized;
}

//    (mimeType){"", ""}, No without the "(mimeType)" it's working lol c con :)
static  mimeType    mimetable[] = {
        {"image/jpeg", ".jpg"},
        {"image/jpeg", ".jpeg"},
        {"image/png", ".png"},
        {"image/gif", ".gif"},
        {"text/html", ".htm"},  // lol ,htm ce koi 7 extention
        {"text/html", ".html"},
        {"text/css", ".css"},
        {"text/plain", ".c"},
        {"text/plain", ".cpp"},
        {"text/markdown", ".md"},
        {"text/javascript", ".js"}, //  sisi ca me permet de .js le rat
        {"text/gitignore", ".gitignore"},   // this one is made up LOL
        {"", ""} };


std::string     getMimeType(std::string extension)
{
    extension = extensionSanitize(extension);

    for (int i = 0; mimetable[i].type.size() > 0 && extension.size() > 0; i++)
    {
        if (!extension.compare(mimetable[i].extension))
            return mimetable[i].type;
    }

    //  massive security breach LOL
    return "text/plain";
}