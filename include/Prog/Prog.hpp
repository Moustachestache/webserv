
#pragma once

# include "../main.hpp"

class	TcpServer;

class Prog
{
	public:

		Prog( void );
		~Prog();

		void	parseFile( char *filePath );

		std::string	getServerStrDebug( void );

		void	startAllServers( void );

	private:

		void	removeComment( std::string &fileContent );
		void	getServerStr( std::string &fileContent );

		std::vector < TcpServer * >	_servers;

};
