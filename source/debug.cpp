
#include "../include/Route/Route.hpp"
#include "../include/Server/Server.hpp"

std::string	Route::getVarStr( void )	/*	DEBUG PRINT FUNCTION	*/
{
	std::string res;
	res.append("\n\n\tROUTE[");
	res.append(_path);
	res.append("]\n\t{\n\t\tMETHOD =");
	for (std::vector< std::string >::iterator it = _methods.begin(); it != _methods.end(); it++ )
	{
		res.append(" ");
		res.append(*it);
	}
	res.append("\n\t\tREDIRECTION = ");
	res.append(_redirection);
	res.append("\n\t\tLISTING = ");
	if (_listing)
		res.append("allow");
	else
		res.append("forbid");
	res.append("\n\t\tDEFAULT =");
	for (std::vector< std::string >::iterator it0 = _defaultPages.begin(); it0 != _defaultPages.end(); it0++ )
	{
		res.append(" ");
		res.append(*it0);
	}
	res.append("\n\t\tALLOW_UPLOAD = ");
	if (_allowUpload)
		res.append("allow");
	else
		res.append("forbid");
	res.append("\n\t\tUPLOAD_PATH = ");
	res.append(_uploadPath);
	res.append("\n\t\tSESSION_TIMEOUT = ");
	res.append(ft_itoa(_sessionTimeout));
	for (std::vector< Cgi >::iterator it = _cgi.begin(); it != _cgi.end(); it++ )
	{
		res.append("\n\n\t\tCGI[");
		res.append((it)->name);
		res.append("]\n\t\t{\n\t\t\tPATH = ");
		res.append((it)->path);
		res.append("\n\t\t\tEXTENSION = ");
		for (std::vector< std::string >::iterator it2 = it->extention.begin(); it2 != it->extention.end(); it2++ )
		{
			res.append(" ");
			res.append(*it2);
		}
		res.append("\n\t\t}");
	}
	res.append("\n\t}\n");
	return (res);

}

std::string	Server::getVarStr( void )	/*	DEBUG PRINT FUNCTION	*/
{
	std::string res;
	res.append("server[");
	res.append(_ipStr);
	res.append(":");
	res.append(ft_itoa(_port));
	res.append("]\n{\n\tSERVER_NAME = ");
	res.append(_serverName);
	res.append("\n\tCONTACT = ");
	res.append(_contact);
	res.append("\n\tROOT = ");
	res.append(_root);
	res.append("\n\tMAX_HEADER_SIZE = ");
	res.append(ft_itoa(_maxHeaderSize));
	res.append("\n\tREQUEST_SIZE = ");
	res.append(ft_itoa(_requestSize));
	for (std::vector< Route >::iterator it = _route.begin(); it != _route.end(); it++ )
		res.append(it->getVarStr());
	res.append("\n\tMAX_CONNECTIONS = ");
	res.append(ft_itoa(_maxConnections));
	res.append("\n\tERROR_LOG = ");
	res.append(_errorLog);
	res.append("\n}\n");
	return (res);
}