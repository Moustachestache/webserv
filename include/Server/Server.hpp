/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbricot <gbricot@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 09:03:43 by gbricot           #+#    #+#             */
/*   Updated: 2024/05/12 12:45:26 by gbricot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

# include "../main.hpp"
//# include "../confKeywords.hpp"

# include <iostream>
# include <vector>

class	Route;

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