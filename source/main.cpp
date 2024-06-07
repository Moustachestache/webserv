/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbricot <gbricot@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 09:03:05 by gbricot           #+#    #+#             */
/*   Updated: 2024/06/03 14:48:50 by gbricot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/main.hpp"

bool	ServerRunning = 1;

std::string	returnFileStr( std::string fileName )
{
	std::ifstream	file;

	file.open(fileName.c_str(), std::ifstream::in);
	if (!file.is_open())
		return ("");
	std::string fileContent((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
	file.close();
	return (fileContent);
}

void	stopServer( int sig )
{
	(void) sig;
	std::cout << "\nStoping server..." << std::endl;
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
		//std::cout << "Parsing OK" << std::endl;
		//std::cout << data.getServerStrDebug() << std::flush;
		data.startAllServers();
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << std::endl;
		return (1);
	}
}