
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

class	WrongHeader : public std::exception
{

		public:

			virtual const char* what( void ) const throw();
};

class	WrongVariableAssignment : public std::exception
{

		public:

			virtual const char* what( void ) const throw();
};

class	WrongHttpErrorNumber : public std::exception
{

		public:

			virtual const char* what( void ) const throw();
};



