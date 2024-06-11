//#include "Cgi.hpp"

#include "../TcpServer/TcpServer.hpp"
#include <algorithm>
/*char **make_arg(HttpHeader _header)
{
	char *arg[_header.getArgs().size() + 2];
	arg[0] = strdup(_header.getFile().c_str());
	for (size_t i = 1; i < _header.getArgs().size(); i++)
	{
		arg[i] = strdup(_header.getArgs()[i].c_str());
	}
	arg[_header.getArgs().size() + 1] = NULL;
	return arg;
}*/

// void display_args(std::vector<std::string> tab)
// {

// 	for(map<std::string , std::string >::iterator it =tab.begin() ;i < tab.size(); i++)
// 	{
// 		std::cout << tab[i] << std::endl;
// 	}
// }


std::string TcpServer::cgiPath(std::vector<Route> routes, HttpHeader _header)
{
	std::string file_verif;
	for (std::vector<Route>::iterator it = routes.begin(); it != routes.end(); ++it)
	{
		checkValidRoute(_header, *it, file_verif);
		if (!file_verif.empty())
		{
			if (file_verif.at(file_verif.size() -1) != '/')
			{
				if (!(*it).getCgi().empty())
				{
					for(std::size_t i = 0; i < (*it).getCgi().size(); i++ )
					{
						for (std::size_t j = 0; j < (*it).getCgi()[i].extention.size(); j++)
						{
							if(file_verif.substr(file_verif.find_last_of(".")) == (*it).getCgi()[i].extention[j])
								return (*it).getCgi()[i].path;
						}
					}
				}
			}
		}
	}
	addLog("Not Path implemented for this extension");
	return 0;
} 

std::string	TcpServer::true_path(std::vector<Route> _routes, HttpHeader _header)
{
	std::string file_verif;
	for (std::vector<Route>::iterator it = _routes.begin(); it != _routes.end(); ++it)
	{
		checkValidRoute(_header, *it, file_verif);
		if(!file_verif.empty())
			return file_verif;
	}
	return 0;
}


bool TcpServer::isCgi(std::vector<Route> route, HttpHeader &_header)
{
	std::string file_verif;
	for (std::vector<Route>::iterator it = route.begin(); it != route.end(); ++it)
	{
		checkValidRoute(_header, *it, file_verif);
		if (!file_verif.empty())
		{
			if (file_verif.at(file_verif.size() -1) != '/')
			{
				if (!(*it).getCgi().empty())
				{
					for(std::size_t i = 0; i < (*it).getCgi().size(); i++ )
					{
						for (std::size_t j = 0; j < (*it).getCgi()[i].extention.size(); j++)
						{
							if(file_verif.substr(file_verif.find_last_of(".")) == (*it).getCgi()[i].extention[j])
								return true;
						}
					}
					return false;
				}
				else
				{
					addLog("CGI Not implemented");
					return false;
				}
			}
		}
	}
	addLog("Route CGI Not implemented");
	return false;
}


void TcpServer::execCgi(HttpHeader _header, std::string true_path, std::vector<Route> routes)
{
	std::string answer;
	std::string _path;

	_path = cgiPath(routes, _header);

	//display_args(_header.getArgv())
	if (_header.getMethod() == "GET"  || _header.getMethod() == "POST") 
	{
		answer = (execCgiGet(_header, true_path, _path));
	}

	if (!answer.empty())
	{
		answer.insert(0,  buildHeader(".html" , 200, answer.size(), routes));
		send(_newSocket, answer.c_str(), answer.size(), 0);
	}
	else
	{
		//page d'erreur;
	}
	
	//envoyer une page d'erreur
	//return (0);
}

std::string TcpServer::execCgiGet(HttpHeader _header, std::string true_path, std::string _path)
{
	int pipe_fd[2];
	pid_t pid;

	(void) _header;
	if (pipe(pipe_fd) == -1) {
        std::cerr << "pipe failed" << std::endl;
        exit(1);
    }

	std::cout << "Lapis Lazuli" << std::endl;
	pid = fork();

	if (pid == -1)
	{
		std::cerr << "fork failed" << std::endl;
		exit(1);
	}
	else if (pid == 0)
	{

		close(pipe_fd[0]);
        dup2(pipe_fd[1], STDOUT_FILENO); 
        close(pipe_fd[1]);
		
		
		std::string file = true_path; //// faire un getteur pour la Root
		char *script_path = const_cast<char *>(file.c_str());
		char *_pat = const_cast<char *>(_path.c_str());

		std::vector<std::string> argv = _header.getArgv();
        argv.push_back(script_path);
		argv.push_back(_pat);
		std::swap(argv[0], argv[argv.size()-1]);
		std::swap(argv[1], argv[argv.size()-2]);

/* 		if(_header.getMethod() == "GET" && !_header.getGet().empty())
		{
			for(std::map<std::string, std::string>::iterator it = _header.getGet().begin(); it != _header.getGet().end(); it++)
				argv.push_back(it->second);			
		}
		else if (_header.getMethod() == "POST" && !_header.getPost().empty())
		{
			for(std::map<std::string, std::string>::iterator it = _header.getPost().begin(); it != _header.getPost().end(); it++)
				argv.push_back(it->second);
		} */

	    std::vector<char*> args;
        for (size_t i = 0; i < argv.size(); i++)
        {
            args.push_back(const_cast<char*>(argv[i].c_str()));
        }
        args.push_back(NULL);

		char *envp[] = { NULL };

		if (execve(_pat, args.data(), envp) == -1)
			std::cerr << "execve failed" << std::endl;
		exit(0);

	}
	else
	{
		close(pipe_fd[1]);
		waitpid(pid, NULL, 0);

		char buffer[1024];
		int ret;

		std::string answer;	

		while ((ret = read(pipe_fd[0], buffer, 1024)) > 0)
		{
			answer.append(buffer, ret);
		}
		close(pipe_fd[0]);
		
		return (answer);
	}
}
