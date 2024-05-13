/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbricot <gbricot@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 09:03:43 by gbricot           #+#    #+#             */
/*   Updated: 2024/05/12 15:51:49 by gbricot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#pragma once

# include "../main.hpp"

class	Route;

class	Server
{
	public:

		Server( void );
		~Server();
		std::string	outputErrorPage(int id, std::string host, std::string server);
	
	private:
		HttpError				_httpError;
		std::string				_host;
		int						_port;
		std::string				_serverName;
		std::string				_root;
		int						_requestSize;
		std::vector< Route >	_route;

};
