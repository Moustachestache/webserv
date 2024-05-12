
#pragma once

# include "../main.hpp"

class	Server;

class Prog
{

	public:

		Prog( void );
		~Prog();

		void	parseFile( char *filePath );

	private:

		std::vector < Server * >	_servers;

};
