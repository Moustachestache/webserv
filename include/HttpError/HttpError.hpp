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

        /*      CONSTRUCTOR/DESTRUCTOR      */

        HttpError();
        HttpError(HttpError &obj);
        ~HttpError();

        /*      OPERATOR OVERLOADING        */

        HttpError  &operator=( HttpError &cpy );

        //      getters and setters
        const errorinfo getInfo(int id);
        void            addErrorPage(int id, std::string page);

    protected:
        std::map < int, errorinfo > _errorList;
        static int      ErrNumArray[];
};