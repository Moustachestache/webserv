
#include "TcpServer.hpp"

bool	TcpServer::checkAllDefaultPages( std::vector< std::string > &pages, std::string &fullPath )
{
	for (std::vector < std::string >::iterator it = pages.begin(); it != pages.end(); it++)
	{
		fullPath.append(*it);
		if (!access( fullPath.c_str() , R_OK))
		{
			addLog( "Server answer: 200" );
			std::string	awnser = returnFileStr(fullPath);
			awnser.insert(0,  buildHeader((*it).substr((*it).find_last_of("."), std::string::npos),\
				200, awnser.size(), getRoute(), _cookieHeader));
			send(_newSocket, awnser.c_str(), awnser.size(), 0);
			return (true);
		}
		fullPath.resize(fullPath.size() - ((*it).size()));
	}
	return (false);
}

//	build webpage that lists folder
//	struct dirent *readdir(DIR *dirp);
void	TcpServer::ServerAnswerLs(HttpHeader &header, std::string path)
{
	//unsigned long		sent;
	std::string			output;
	DIR					*openDir = opendir(path.c_str());

	if (openDir == NULL)
	{
		ServerAnswerError(500);
		return ;
	}
	output.append("<!DOCTYPE html><html data-theme=\"dark\"><head><link rel=\"stylesheet\" href=\"https://cdn.jsdelivr.net/npm/@picocss/pico@2/css/pico.min.css\"/><link rel=\"stylesheet\" href=\"https://cdn.jsdelivr.net/npm/@picocss/pico@2/css/pico.colors.min.css\" /><link href=\"https://unpkg.com/boxicons@2.1.4/css/boxicons.min.css\" rel=\"stylesheet\"><title>");
	output.append(_serverName + header.getFile() + " folder listing</title></head><body><div class=\"container\"><h1 class=\"grid\">index of " + header.getFile() + "</h1><table><th></th><th>type</th><th>name</th><th>mime/type</th>");
	for (dirent	*folderScan = readdir(openDir); openDir != NULL && folderScan != NULL; folderScan = readdir(openDir))
	{
		output.append("<tr class=\"pico-background-grey-850\">");
		if (folderScan->d_type == DT_DIR)
			output.append("<td><i class=\"bx bx-folder\"></i></td><td>folder</td>");
		else if (folderScan->d_type == DT_REG)
			output.append("<td><i class=\"bx bxs-file\"></i></td><td>file</td>");
		else if (folderScan->d_type == DT_UNKNOWN)
			output.append("<td><i class=\"bx bx-meh-blank\"></i></td><td>thing</td>");
		output.append("<td><a href=\"./");
		output.append(folderScan->d_name);
		if (folderScan->d_type == DT_DIR)
			output.append("/");
		output.append("\">");
		output.append(folderScan->d_name);
		output.append("</a></td><td>");
		if (folderScan->d_type == DT_DIR)
			output.append("folder");
		else
			output.append(getMimeType(folderScan->d_name));
		output.append("</td>");
		output.append("</tr>");
	}
	output.append("</table></div></body>");
	closedir(openDir);
	addLog( "Server answer: 200" );
	output.insert(0, buildHeader(".html", 200, output.size(), getRoute(), _cookieHeader));
	send(_newSocket, output.c_str(), output.size(), 0);
}

void	TcpServer::ServerAnswerGet( HttpHeader &header )
{
	std::vector< Route >	route = getRoute();
	std::string	res;

	for (std::vector<Route>::iterator it = route.begin(); it != route.end(); it++)
	{
		if (std::find((*it).getMethods().begin(), (*it).getMethods().end(), header.getMethod())\
			!= (*it).getMethods().end())
		{
			checkValidRoute(header, *it, res);
			if (!res.empty())
			{
				if (res.at(res.size() - 1) == '/') /*	path is directory	*/
				{
					if (!checkAllDefaultPages( (*it).getDefaultPages(), res))
					{
						if ((*it).getAllowListing())
							ServerAnswerLs( header, res );
						else
							ServerAnswerError(404); /*	Unauthorized listing	*/ 
					}
				}
				else /*	path is file	*/
				{
					addLog( "Server answer: 200" );
					std::string	awnser = returnFileStr(res);
					std::string	extension;
					if (res.find_last_of(".") != std::string::npos)
						extension = res.substr(res.find_last_of("."));
					awnser.insert(0,  buildHeader(extension, 200,\
						awnser.size(), getRoute(), _cookieHeader));
					send(_newSocket, awnser.c_str(), awnser.size(), 0);
				}
				return ;
			}
		}
		else if (it + 1 == route.end())
		{
			ServerAnswerError(405);
			return ;
		}
	}
	ServerAnswerError(404);
}