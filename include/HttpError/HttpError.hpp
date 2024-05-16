#pragma once

#include <iostream>
#include <map>

struct  errorinfo {
    int         code;
    std::string type;
    std::string info;
    std::string file;
};

class   HttpError
{

    public:
        HttpError();
        HttpError(HttpError &obj);
        HttpError &operator=(HttpError &obj);
        ~HttpError();
        //      "database" of http errors. used to setup ErrNumArray.
        static errorinfo   initInfo(int id);

        //      getters and setters
        const errorinfo getInfo(int id);
        void            addErrorPage(int id, std::string page);

    protected:
        std::map < int, errorinfo > _errorList;
        static int      ErrNumArray[];
};