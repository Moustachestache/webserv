#include "Cookies.hpp"

std::string generateSessionId() {
    std::stringstream ss;
    ss << std::time(nullptr) << rand();
    return ss.str();
}

std::string createSession() {
    std::string sessionId = generateSessionId();
    std::ofstream sessionFile("sessions/" + sessionId);
    if (sessionFile.is_open()) {
        // Stocke des données de session (par exemple, une chaîne vide)
        sessionFile << "";
        sessionFile.close();
    }
    return sessionId;
}

std::string getSessionData(const std::string& sessionId) {
    std::ifstream sessionFile("sessions/" + sessionId);
    std::string data;
    if (sessionFile.is_open()) {
        std::getline(sessionFile, data);
        sessionFile.close();
    }
    return data;
}

void updateSessionData(const std::string& sessionId, const std::string& data) {
    std::ofstream sessionFile("sessions/" + sessionId);
    if (sessionFile.is_open()) {
        sessionFile << data;
        sessionFile.close();
    }
}

std::string getCookieValue(const std::string& headers, const std::string& cookieName) {
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
    pos += cookieName.length() + 1; // Length of cookieName + "="
    end = cookies.find(";", pos);
    if (end == std::string::npos) {
        end = cookies.length();
    }
    return cookies.substr(pos, end - pos);
}



std::string    Generate_Cookie(std::string& _header)
{
    
     /*response += "Set-Cookie: " + cookieName + "=" + cookieValue + "; Path=/; HttpOnly\r\n";*/    
}