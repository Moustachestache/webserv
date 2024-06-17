#include "Cookies.hpp"

std::map<std::string, Session> sessionStore;

std::string generateSessionId() {
    std::stringstream ss;
    ss << std::time(NULL) << rand();
    return ss.str();
}

Session createNewSession(std::string username) {
    Session session;
    session.sessionId = generateSessionId();
    if(username == "")
        session.username = "Guest";
    else
        session.username = username;
    return session;
}


std::string getSessionData(const std::string& sessionId) {

    /*std::map<std::string, Session>::const_iterator jt;
    for (jt = sessionStore.begin(); jt != sessionStore.end(); ++jt) {
        std::cout << "Key: " << jt->first << "\n";
        std::cout << "Session ID: " << jt->second.sessionId << "\n";
        std::cout << "Username: " << jt->second.username << "\n";
        std::cout << "-----------------------\n";
    }*/

    std::string data = "";
    std::string post_cookies = "GET_Cookie_name=";
    
    std::string id = sessionId.substr( sessionId.find('=') + 1);
    std::map<std::string, Session >::iterator it = sessionStore.find(id);
    std::cout << "Rubis 3 :" << it->first << "FinRUbis3" <<std::endl;

    if (it != sessionStore.end()) 
    {
        data  = it->second.username;
    }
    else
        return "";
    post_cookies.append(data);
    //post_cookies.append("\r\n");

    std::cout << "Rubis : data::" << data << " post_cookies:" << post_cookies << std::endl; 
    
    return post_cookies;
}

std::string getCookieValue(const std::string& headers, const std::string& cookieName)
{
    size_t pos = headers.find("Cookie: ");
    if (pos == std::string::npos) {
        return "";
    }
    pos += 8; // Length of "Cookie: "
    size_t end = headers.find("\r\n", pos);
    std::string cookies = headers.substr(pos, end - pos);
    
    pos = cookies.find(cookieName + "=");
    if (pos == std::string::npos) {
        return "";
    }
    pos += cookieName.length() + 1; 
    end = cookies.find(";", pos);
    if (end == std::string::npos) {
        end = cookies.length();
    }
    return cookies.substr(pos, end - pos);
}

std::string generateCookieHeader(const std::string& requestHeaders) {
    std::string cookieName = "sessionid";
    std::string cookieValue = getCookieValue(requestHeaders, cookieName);
    std::string cookieHeader;

    if (!cookieValue.empty())
        if (sessionStore.find(cookieValue) != sessionStore.end()) 
            return "";

    Session newSession = createNewSession();
    sessionStore[newSession.sessionId] = newSession;
    
    cookieHeader = "Set-Cookie: " + cookieName + "=" + newSession.sessionId + "; Path=/; HttpOnly\r\n";
    //cookieHeader.append(getSessionData(requestHeaders));
    return cookieHeader;
}

