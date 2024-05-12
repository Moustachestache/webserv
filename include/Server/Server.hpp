/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbricot <gbricot@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 09:03:43 by gbricot           #+#    #+#             */
/*   Updated: 2024/05/12 09:24:59 by gbricot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

# include "../Route/Route.hpp"

# include <iostream>
# include <vector>

class	Server
{
	public:

		Server( void );
		~Server();
	
	private:

		std::string				host;
		int						port;
		std::string				serverName;
		std::string				root;
		int						requestSize;
		std::vector< Route >	route;

};