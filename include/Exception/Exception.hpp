
#pragma once

# include <exception>

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

class	FileNameError : public std::exception
{

		public:

			virtual const char* what( void ) const throw();
};

class	WrongPath : public std::exception
{

		public:

			virtual const char* what( void ) const throw();
};

class	NoMethod : public std::exception
{

		public:

			virtual const char* what( void ) const throw();
};

class	NoRouteDefined : public std::exception
{

		public:

			virtual const char* what( void ) const throw();
};

class	TooMuchServers : public std::exception
{

		public:

			virtual const char* what( void ) const throw();
};

class	SelectFailed : public std::exception
{

		public:

			virtual const char* what( void ) const throw();
};