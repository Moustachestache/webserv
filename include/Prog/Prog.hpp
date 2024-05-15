
#pragma once

# include "../main.hpp"

class	Server;

class Prog
{
	public:

		Prog( void );
		~Prog();

		void	parseFile( char *filePath );

		std::string	getServerStrDebug( void );

	private:

		void	removeComment( std::string &fileContent );
		void	getServerStr( std::string &fileContent );

		std::vector < Server * >	_servers;

};
