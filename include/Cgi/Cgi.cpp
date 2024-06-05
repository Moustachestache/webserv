//#include "Cgi.hpp"

#include "../TcpServer/TcpServer.hpp"
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

std::string	TcpServer::true_path(std::vector<Route> _routes, HttpHeader _header)
{
	std::string file_verif;
	for (std::vector<Route>::iterator it = _routes.begin(); it != _routes.end(); ++it)
	{
		checkValidRoute(_header, *it, file_verif);
		if(file_verif.empty())
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
		return false;
}


std::string TcpServer::execCgi(HttpHeader _header, std::string true_path)
{
	/*std::cout << std::endl << "Lapis Lazuli" << std::endl;
	std::cout << std::endl << "Method : " << _header.getMethod() << std::endl;
	for (std::map<std::string, std::string >::iterator it  = _header.getArgs().begin(); it != _header.getArgs().end(); ++it)
	{
		std::cout << it->first << " => " << it->second << std::endl;
	}	
	std::cout << "Fin Lapis Lazuli" << std::endl;
	return ;*/
	/*if (_header.getMethod() == "POST")
	{
		execCgiPost(_header);
	}
	else*/ if (_header.getMethod() == "GET")
	{
		return (execCgiGet(_header, true_path));
	}
	return (0);
}

std::string TcpServer::execCgiGet(HttpHeader _header, std::string true_path)
{
	int pipe_fd[2];
	pid_t pid;

	
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
		char *argv[] = { script_path, NULL };
		char *envp[] = { NULL };

		if (execve(script_path, argv, envp) == -1)
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
