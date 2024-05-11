# webserv
## a C++98 standard http server

##	Exploratory Qs
what does a default .conf look like? what do we expect from it?

what path does data take from A to Z.

how is data uploaded? how do you send a form?

where does CGI fit into this? what even is it?

who is EOF

what is chunked request? How to unchunk?

##	RFC / Documentation
HTTP/1.1 reference:	https://datatracker.ietf.org/doc/html/rfc9112

HTTP caching (2022):	https://datatracker.ietf.org/doc/html/rfc9111

HTTP Message Syntax and Routing (2024): https://datatracker.ietf.org/doc/html/rfc6585

Additional HTTP status codes: https://datatracker.ietf.org/doc/html/rfc6585

CGI specification document: https://www.rfc-editor.org/info/rfc3875

##	links
CGI on Wikipedia: https://en.wikipedia.org/wiki/Common_Gateway_Interface

NGINX default .conf:    https://www.nginx.com/resources/wiki/start/topics/examples/full/

apache server Documentation:    https://httpd.apache.org/docs/current/

some video  on cgi: https://www.youtube.com/watch?v=sSy5EdRd7zc&ab_channel=Homedeve

some other video: https://www.youtube.com/watch?v=eFCiNdY8CS4&ab_channel=ControllersTech

get and post: https://www.ionos.fr/digitalguide/sites-internet/developpement-web/get-vs-post/

##  .conf file components
- Chose port and host of each server.
- Setup server name or not.
- first server for a host:port is the default. it answers all requests that are undefined.
- setup default error pages.
- (?) limit client body size
setup routes with one or more of the following rules:
    - Define a list of accepted HTTP methods.
    - Define a HTTP redirection
    - Define a directory or a file from where the file should be searched. Aka define root folder.
    - turn on or off directory listing.
    - set a default file to answer if the request is a directory.
    - Execute CGI based on a certain file extension.
    - make it work with POST / GET method.
    - Make the route able to accept uploaded files, and configure where they should be saved.