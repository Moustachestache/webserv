
#include "../include/main.hpp"

bool	ServerRunning = 1;

void	stopServer( int sig )
{
	(void) sig;
	std::cout << "\r\nStopping server..." << std::endl;
	ServerRunning = 0;
}

int	main( int ac, char **av )
{
	if (ac != 2)
	{
		std::cerr << "Wrong number of argument. Usage: ./webserv [configuration file]" << std::endl;
		return (1);
	}
	signal(SIGINT, stopServer);
	Prog	data( ServerRunning );
	try
	{
		data.parseFile( av[1] );
		std::cout << data.getServerStrDebug() << std::flush; // debug: print the parsed values
		data.startAllServers();
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << std::endl;
		return (1);
	}
}