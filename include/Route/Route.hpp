
#pragma once

# include <vector>
# include <fstream>
# include <sstream>
# include <iostream>
# include <vector>
# include <string>

# include "../Exception/Exception.hpp"
# include "../../source/assignSingleValue.tpp"

std::string	returnFileStr( std::string fileName );

size_t	getChunkStart( std::istringstream &iss, std::string &fileContent, std::string chunkName );
size_t	getNextBracket( std::string &fileContent, size_t pos);
size_t	getChunkEnd( std::string &fileContent, size_t pos );
std::string	getHeaderStr( std::string &chunkStr );
std::string	ft_itoa( int val );
int	ft_atoi( std::string &nb );
void	checkValidIp( std::string &ip );
bool	isPathRelative( std::string &path );
unsigned int	strIpToUint( std::string &ip );
std::string	BuildRelativePath( std::string first, std::string second, std::string third );

struct Cgi
{
	std::string					name;
	std::string					path;
	std::vector < std::string >	extention;
};


class Route
{
	public:

		/*		CONSTRUCTORS/DESTRUCTOR		*/

		Route( void );
		Route( Route &cpy );
		Route( std::string &routeStr );
		~Route();

		/*		OPERATOR OVERLOADING		*/

		Route	&operator=( Route &cpy );

		/*		DEBUG		*/

		std::string	getVarStr( void );

		/*		GETTERS		*/

		std::vector< std::string >	&getMethods( void );
		std::string	&getPath( void );
		std::string	&getRedirection( void );
		std::vector<std::string>	&getDefaultPages( void );
		std::vector< Cgi >			&getCgi( void );
		bool	getAllowListing( void );
		bool	getAllowUpload( void );
		std::string	getUploadPath( void );

	private:

		/*		PARSING		*/

		void	checkInfo( void );
		void	processCgi( std::string &cgi );
		void	getVarContentRoute( std::string &line, Cgi &nCgi );
		void	assignMultipleValue( std::istringstream &iss, std::vector< std::string > &vec );
		void	getAllCgi( std::string &routeStr );
		void	getAllVariables( std::string &routeStr );
		void	getVarContentRoute( std::string &line );

	

		std::string					_path;
		std::vector < std::string >	_methods;
		std::string					_redirection;
		bool						_listing;
		std::vector < std::string >	_defaultPages;
		bool						_allowUpload;
		std::string					_uploadPath;
		int							_sessionTimeout;
		std::vector < Cgi >			_cgi;

};

