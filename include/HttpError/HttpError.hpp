#pragma once

#include <map>
#include <iostream>

#define HTTP_ERR_NUM {\
            100, 101, \
            200, 201, 202, 203, 203, 205, 206, \
            300, 301, 302, 303, 304, 305, 306, 307, \
            400, 401, 402, 403, 404, 405, 406, 407, 408, 409, 410, 411, 412, 413, 414, 415, 416, 417, \
            500, 501, 502, 503, 504, 505\
};

struct  errorinfo {
    int         code;
    std::string type;
    std::string info;
    std::string file;
};

class   HttpError {
    public:
        HttpError();
        HttpError(HttpError &obj);
        HttpError &operator=(HttpError &obj);
        ~HttpError();
        errorinfo   getInfo(int id);
        void        addErrorPage(int id, std::string page);
        errorinfo   initInfo(int id);
    private:
        std::map < int, errorinfo > _errorList;
};