/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbricot <gbricot@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 09:03:05 by gbricot           #+#    #+#             */
/*   Updated: 2024/05/12 12:52:50 by gbricot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/main.hpp"

int	main( int ac, char **av)
{
	if (ac != 2)
	{
		std::cerr << "Wrong number of argument. Usage: ./webserv [configuration file]" << std::endl;
		return (1);
	}
	Prog	data;
	try
	{
		data.parseFile( av[1] );
		
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << std::endl;
		return (1);
	}
}