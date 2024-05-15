
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

class	SocketError : public std::exception
{

		public:

			virtual const char* what( void ) const throw();
};

class	ConnectError : public std::exception
{

		public:

			virtual const char* what( void ) const throw();
};

class	ListenFailed : public std::exception
{

		public:

			virtual const char* what( void ) const throw();
};

class	NewSocketError : public std::exception
{

		public:

			virtual const char* what( void ) const throw();
};

class	IncomingBytesFailed : public std::exception
{

		public:

			virtual const char* what( void ) const throw();
};

class	AnswerFailure : public std::exception
{

		public:

			virtual const char* what( void ) const throw();
};