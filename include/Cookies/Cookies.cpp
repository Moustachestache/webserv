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

void setSessionData(const std::string sessionId, const std::string userName)
{
    std::cout << "Diamant" << sessionId << " " << userName << std::endl;
    if (sessionId != "" && userName != "")
    {
        std::string ses = sessionId.substr(sessionId.find("=") + 1);
        std::cout << "Diamant2" << ses << std::endl;
        if(ses != "")
        {
            std::map< std::string, Session>::iterator it  = sessionStore.find(ses);
            std::cout << "Diamant3" << it->first <<" " <<it->second.sessionId << " " << it->second.username << std::endl;
            if (it != sessionStore.end())
            {
                it->second.username = userName;
            }
        }
    }
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

bool getCookieValue(const std::string& headers, const std::string& cookieName)
{

    //si il y a un cookie --> on retourne une chaine vide
    std::cout << "Lapis Lazuli " << headers << std::endl;
    std::size_t pos  = headers.find(cookieName);
    if (pos  == std::string::npos) // y a pas de cookie
        return true;

    //si il y  a un cookie mais qu'il y a déjà la session existante renvoyer aussi une chaine vide
    pos += 10 ;
    std::size_t end = headers.find("\r\n", pos);
    std::string cookies = headers.substr(pos, end - pos);
        std::cout << "Lapis Lazuli 2 " << cookies << sessionStore[cookies].username << std::endl;
    if (sessionStore.find(cookies) ==  sessionStore.end())//si il y  a un cookie mais qu'il y a déjà la session existante renvoyer aussi une chaine vide
        return true;
    else
        return false;
}

//on envoie un Set cookie si il n'y a pas de cookie ou si le cookie prit en compte n'as pas de session
std::string generateCookieHeader(const std::string& requestHeaders) {


    std::string cookieName = "sessionid=";
    bool cookieValue = getCookieValue(requestHeaders, cookieName);
    std::string cookieHeader;

    if (!cookieValue) 
            return "";

    Session newSession = createNewSession();
    sessionStore[newSession.sessionId] = newSession;
    
    cookieHeader = "Set-Cookie: " + cookieName + "=" + newSession.sessionId + "; Path=/; HttpOnly\r\n";
    //cookieHeader.append(getSessionData(requestHeaders));
    return cookieHeader;
}

