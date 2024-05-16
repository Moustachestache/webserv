/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbricot <gbricot@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 09:03:43 by gbricot           #+#    #+#             */
/*   Updated: 2024/05/15 14:27:50 by gbricot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

# include <iostream>
# include <vector>
# include <fstream>
# include <sstream>

//# include "../main.hpp"

# include "../HttpError/HttpError.hpp"
# include "../Exception/Exception.hpp"
# include "../Route/Route.hpp"

template < typename V >
void	assignSingleValue( std::istringstream &iss, V &to_assign )
{
	std::string	sep;
	V word;
	if (!(iss >> sep))
		throw WrongVariableAssignment();
	else if (sep.compare("="))
		throw WrongVariableAssignment();
	else if (!(iss >> word))
		throw WrongVariableAssignment();
	to_assign = word;
}

class	Route;

class	Server
{
	public:

		Server( void );
		Server( std::string &serverStr );
		~Server();
		std::string	outputErrorPage(int id);

		void	getVarContent( std::string &buffer, std::istringstream &iss );
		void	getAllVariables( std::string &serverStr );
		void	checkServerHeader( std::string &serverStr );
		void	getAllRoutes( std::string &serverStr, std::string name );
		void	getAllErrors( std::string &serverStr, std::string name );
		void	addError( std::string &errorStr );
		void	assignError( std::istringstream &iss );

		/*		DEBUG		*/
		std::string	getVarStr( void );
	
	protected:
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

