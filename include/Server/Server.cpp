
#include "Server.hpp"

Server::Server( void )
{
	
}

Server::Server( std::string &serverStr )
{
	(void) serverStr;
}

Server::~Server( )
{
	
}

std::string Server::outputErrorPage(int id)
{
	std::string strFile = returnFileStr(_httpError.getInfo(id).file.c_str());
	if (strFile.empty())
	{
		strFile.append("<!DOCTYPE html><html style=\"background-color: black; color: white; text-align: center;font-family: system-ui;\"><head><title>");
		strFile.append(_httpError.getInfo(id).type);
		strFile.append("</title><img src=\"https://i.imgur.com/qWMCwWS.gif\"/><h1>");
		std::stringstream itoa;
		itoa << id;
		strFile.append(itoa.str());
		strFile.append(" - ");
		strFile.append(_httpError.getInfo(id).type);
		strFile.append("</h1><h3>");
		strFile.append(_httpError.getInfo(id).info);
		strFile.append("</h3>contact your local admin at ");
		strFile.append(_contact);
		strFile.append("</body></html>");
	}
	return strFile;
}
/*
<!DOCTYPE html><html style="background-color: black; color: white; text-align: center;font-family: system-ui;"><head><title>
error
</title><img src="https://i.imgur.com/qWMCwWS.gif"/><h1>
error
</h1><h3>
this is the error text
</h3>contact your local admin at 
$var@$var
</body></html>
*/