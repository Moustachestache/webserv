/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbricot <gbricot@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 09:03:43 by gbricot           #+#    #+#             */
/*   Updated: 2024/05/15 13:42:50 by gbricot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

# include "../main.hpp"
# include "../HttpError/HttpError.hpp"
# include "../TcpServer/TcpServer.hpp"

class	Route;

class	Server
{
	public:

		Server( void );
		Server( std::string &serverStr );
		~Server();
		std::string	outputErrorPage(int id);
		void	ServerListen();
		void	ServerAnswer();

		/*		DEBUG		*/
		std::string	getVarStr( void );
	
	protected:
		TcpServer				_tcpServer;
		HttpError				_httpError;
		std::string				_ipStr;
		long int				_ip;
		std::string				_contact;
		int						_port;
		std::string				_serverName;
		std::string				_root;
		int						_requestSize;
		int						_maxConnections;
		std::vector< Route >	_route;
		int						_maxConnections;
		std::string				_errorLog; //lol

};
