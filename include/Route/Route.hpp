
#pragma once

#include <iostream>
#include <vector>

class Route
{
	public:

		Route( void );
		~Route();

	private:

		std::string					path;
		std::vector < std::string >	methods;
		std::string					redirection;
		std::string					listing;
		std::vector < std::string >	defaultPages;
		bool						allowUpload;
		std::string					uploadPath;
		int							sessionTimeout;

};

