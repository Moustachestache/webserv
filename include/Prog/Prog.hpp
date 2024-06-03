
#pragma once

# include "../main.hpp"

class	TcpServer;

class Prog
{
	public:

		Prog( bool &ServerRunning );
		~Prog();

		void	parseFile( char *filePath );

		std::string	getServerStrDebug( void );

		void	startAllServers( void );

	private:

		void	removeComment( std::string &fileContent );
		void	getServerStr( std::string &fileContent );
		void	ServerRoutine( void );

		std::vector < TcpServer * >	_servers;

		fd_set	fdSet;
		bool	&_serverRunning;

};
