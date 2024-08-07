#include "../include/main.hpp"

static std::string	getAllUsedMethods( std::vector< Route * > &allRoutes )
{
	std::string res;
	for (std::vector< Route * >::iterator it = allRoutes.begin(); it  != allRoutes.end(); it++ )
	{
		for (std::vector< std::string >::iterator itMethods = (*it)->getMethods().begin(); \
					itMethods != (*it)->getMethods().end(); itMethods++ )
		{
			if (res.find(*itMethods) == std::string::npos)
				res.append(" " + *itMethods + ",");
		}
	}
	if (res.rfind(",") != std::string::npos)
		res.erase(res.rfind(","), 1);
	res.append("\r\n");
	return (res);
}

std::string	buildHeader(std::string extension, int errorcode, int contentSize, \
												std::vector< Route * > &allRoutes , std::string cookieHeader)
{
	HttpError	error;
	std::string returnStr("HTTP/1.1 ");

	returnStr.append(" " + ft_itoa(errorcode));
	returnStr.append(" " + error.getInfo(errorcode).type);
	returnStr.append("\r\n");
	returnStr.append(cookieHeader);
	returnStr.append("content-type: " + getMimeType(extension) + "; charset=utf-8\r\n");
	returnStr.append("content-length: " + ft_itoa(contentSize) + "\r\n");
	returnStr.append("accept-encoding: identity\r\n");
	if (errorcode == 405)
	{
		returnStr.append("Allow:");
		returnStr.append(getAllUsedMethods(allRoutes));
	}
	returnStr.append("connection: close\r\n");
	returnStr.append("\r\n");
	return returnStr;
}