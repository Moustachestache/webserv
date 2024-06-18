
#pragma once

# include "../main.hpp"

class	TcpServer;

class Prog
{
	public:

		/*		CONSTRUCTORS/DESTRUCTOR		*/

		Prog( bool &ServerRunning );
		Prog( Prog &cpy );
		~Prog();

		/*		OPERATOR OVERLOADING		*/

		Prog	&operator=( Prog &cpy );

		/*		PARSING		*/

		void	parseFile( char *filePath );

		/*		SERVER ROUTINE		*/

		void	startAllServers( void );

		/*		DEBUG		*/

		std::string	getServerStrDebug( void );

	private:

		void	removeComment( std::string &fileContent );
		void	getServerStr( std::string &fileContent );
		void	ServerRoutine( void );

		std::vector < TcpServer * >	_servers;

		fd_set	fdSet;
		bool	&_serverRunning;

};
