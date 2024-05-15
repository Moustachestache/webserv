
#pragma once

#include <iostream>
#include <vector>

std::string	returnFileStr( std::string fileName );

size_t	getChunkStart( std::istringstream &iss, std::string &fileContent, std::string chunkName );
size_t	getNextBracket( std::string &fileContent, size_t pos);
size_t	getChunkEnd( std::string &fileContent, size_t pos );

struct Cgi
{
	std::string					name;
	std::string					path;
	std::vector < std::string >	extention;
};


class Route
{
	public:

		Route( void );
		Route( std::string &routeStr );
		~Route();

	private:

	void	getAllCgi( std::string &routeStr );

		std::string					_path;
		std::vector < std::string >	_methods;
		std::string					_redirection;
		std::string					_listing;
		std::vector < std::string >	_defaultPages;
		bool						_allowUpload;
		std::string					_uploadPath;
		int							_sessionTimeout;
		std::vector < Cgi >			_cgi;

};

