#include "Cgi.hpp"


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


bool isCgi(Route route, std::string filename)
{
    if (!route.getCgi().empty())
    {
        for(std::size_t i = 0; i < route.getCgi().size(); i++ )
        {
            for (std::size_t j = 0; j < route.getCgi()[i].extention.size(); j++)
            {
                if(filename.substr(filename.find_last_of(".")) == route.getCgi()[i].extention[j])
                    return true;
            }
        }
        return false;
    }
    else
    {
        return false;
    }
}


std::string execCgi(HttpHeader _header)
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
		std::cout << std::endl << "Granit" << std::endl;
		execCgiPost(_header);

	}
	else*/ if (_header.getMethod() == "GET")
	{
		return (execCgiGet(_header));
	}
	return (0);
}

/*void execCgiPost(HttpHeader _header)
{
	//executé le fichier sh via la http request
	int pipe_fd[2];
	pid_t pid;

	pipe(pipe_fd);
	dup2(STDOUT_FILENO, pipe_fd[1]);
	pid = fork();

	if (pid == -1)
	{
		std::cerr << "fork failed" << std::endl;
		exit(1);
	}
	else if (pid == 0)
	{
		//on execute le cgi
		char **argv = make_arg(_header);
		execve(_header.getFile().c_str(), argv, NULL);
		std::cerr << "execve failed" << std::endl;
		exit(0);
	}
	else
	{
		waitpid(pid, NULL, 0);
		//on recupere le resultat
		char buffer[1024];
		int ret;
		while ((ret = read(pipe_fd[0], buffer, 1024)) > 0)
		{
			write(STDOUT_FILENO, buffer, ret);
		}
	}
}*/

std::string execCgiGet(HttpHeader _header)
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
		
		
		std::string file = _header.getFile().insert(0, "./www");
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
		
		std::cout << "Aigue Marine 2 " << answer << "Fin Aigue Marine " <<std::endl ;
		
		return (answer);
	}
}
