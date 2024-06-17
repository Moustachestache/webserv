
#pragma once

# include <ctime>
# include <fstream>
# include "../HttpError/HttpError.hpp"
# include "../Route/Route.hpp"

class	Route;

class	Server
{
	public:

		/*		CONSTRUCTORS/DESTRUCTOR		*/

		Server( void );
		Server( std::string &serverStr );
		Server( Server &cpy );
		~Server();

		/*		OPERATOR OVERLOADING		*/

		Server	&operator=( Server &cpy );

		std::string	outputErrorPage(int id);

		std::vector< Route >	&getRoute( void );

		/*		DEBUG		*/
		std::string	getVarStr( void );
		void	processError( std::string &line );
		
		//	accessors
		size_t		getMaxHeaderSize();
		size_t		getMaxRequestSize();
	
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

		void	addLog( std::string text );

		/*		PROTECTED MEMBERS		*/

		HttpError				_httpError;
		std::string				_ipStr;
		unsigned int			_ip;
		std::string				_contact;
		int						_port;
		std::string				_serverName;
		std::string				_root;
		size_t					_maxHeaderSize; /*	Bytes	*/
		size_t					_requestSize; /*	Bytes	*/
		std::vector< Route >	_route;
		std::string				_errorLog;
};