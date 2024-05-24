/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbricot <gbricot@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 09:03:43 by gbricot           #+#    #+#             */
/*   Updated: 2024/05/22 10:42:50 by gbricot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

# include "../HttpError/HttpError.hpp"
# include "../Route/Route.hpp"

class	Route;

class	Server
{
	public:

		/*		CONSTRUCTORS/DESTRUCTOR		*/

		Server( void );
		Server( std::string &serverStr );
		~Server();


		std::string	outputErrorPage(int id);

		/*		DEBUG		*/
		std::string	getVarStr( void );
		void	processError( std::string &line );
	
	protected:

		/*		PARSING		*/

		void	getVarContentServer( std::string &line );
		void	getAllVariables( std::string &serverStr );
		void	checkServerHeader( std::string &serverStr );
		void	getAllRoutes( std::string &serverStr, std::string name );
		void	getAllErrors( std::string &serverStr, std::string name );
		void	addError( std::string &errorStr );
		void	assignError( std::istringstream &iss );

		void	checkInfo( void );

		/*		PROTECTED MEMBERS		*/

		HttpError				_httpError;
		std::string				_ipStr;
		long int				_ip;
		std::string				_contact;
		int						_port;
		std::string				_serverName;
		std::string				_root;
		int						_maxHeaderSize;
		int						_requestSize;
		std::vector< Route >	_route;
		int						_maxConnections;
		std::string				_errorLog; //lol
};

