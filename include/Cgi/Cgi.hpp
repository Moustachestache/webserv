#pragma once
#include "../main.hpp"


bool isCgi(Route route, std::string filename);

std::string    execCgiPost(HttpHeader _header);
std::string    execCgiGet(HttpHeader _header);
std::string    execCgi(HttpHeader _header);

