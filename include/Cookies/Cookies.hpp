

#pragma once

# include "../main.hpp"


struct Session {
    std::string sessionId;
    std::string username;
};

//extern std::map<std::string, Session> sessionStore;


std::string     generateSessionId();
Session         createNewSession(std::string username="");
bool     getCookieValue(const std::string& headers, const std::string& cookieName);
std::string     getSessionData(const std::string& sessionId) ;
std::string     generateCookieHeader(const std::string& requestHeaders);
void            setSessionData(const std::string sessionId, const std::string userName);

//std::string     generateCookieHeader(const int socket);
