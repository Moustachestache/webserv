#pragma once
#include "../main.hpp"


bool isCgi(Route route, std::string filename);

void    execCgiPost(HttpHeader _header);
void    execCgiGet(HttpHeader _header);
void    execCgi(HttpHeader _header);


