
#pragma once

# include "../main.hpp"

class	UnableToOpenFile : public std::exception
{

		public:

			virtual const char* what( void ) const throw();
};

