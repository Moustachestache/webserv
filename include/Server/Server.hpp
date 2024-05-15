/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbricot <gbricot@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 09:03:43 by gbricot           #+#    #+#             */
/*   Updated: 2024/05/15 10:45:35 by gbricot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

# include "../main.hpp"
# include "../HttpError/HttpError.hpp"

class	Route;

class	Server
{
	public:

		Server( void );
		Server( std::string &serverStr );
		~Server();
		std::string	outputErrorPage(int id);
	
	private:

		void	checkServerHeader( std::string &serverStr );
		void	getAllVariables( std::string &serverStr );
		void	getVarContent( std::string &buffer, std::istringstream &iss );
		void	getAllRoutes( std::string &serverStr, std::string name );
		void	getAllErrors( std::string &serverStr, std::string name );
		void	addError( std::string &errorStr );
		void	assignError( std::istringstream &iss );

		HttpError				_httpError;
		std::string				_ipStr;
		long int				_ip;
		std::string				_contact;
		int						_port;
		std::string				_serverName;
		std::string				_root;
		int						_requestSize;
		std::vector< Route * >	_route;
		std::string				_errorLog; //lol

		

};
