
#pragma once

# include "../main.hpp"

class	UnableToOpenFile : public std::exception
{

		public:

			virtual const char* what( void ) const throw();
};

class	NoServerFound : public std::exception
{

		public:

			virtual const char* what( void ) const throw();
};

class	WrongWord : public std::exception
{

		public:

			virtual const char* what( void ) const throw();
};

class	BracketsError : public std::exception
{

		public:

			virtual const char* what( void ) const throw();
};




