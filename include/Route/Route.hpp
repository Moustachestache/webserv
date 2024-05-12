
#pragma once

#include <iostream>
#include <vector>

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
		~Route();

	private:

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

