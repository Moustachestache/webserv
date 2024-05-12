/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbricot <gbricot@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 09:03:43 by gbricot           #+#    #+#             */
/*   Updated: 2024/05/12 10:59:39 by gbricot          ###   ########.fr       */
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

		std::string				_host;
		int						_port;
		std::string				_serverName;
		std::string				_root;
		int						_requestSize;
		std::vector< Route >	_route;

};