# webserv
## a C++98 standard http server

# TODO
- [ ] how to get a good, clean, scalable buffer for request reception?
- [ ] refactor Errorinfo array creation / init
- [ ] build httpheader object
- [ ] implement "inet_addr()" and "ntohs()" as our own functions
- [ ] why double-up message in answer message?
# DOING

##	Exploratory Qs
what does a default .conf look like? what do we expect from it?

hows an HTTP request built. how do we process it?

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
C++ http server writeup:    https://osasazamegbe.medium.com/showing-building-an-http-server-from-scratch-in-c-2da7c0db6cb7
-> regarding sockaddr_in:   https://www.gta.ufrj.br/ensino/eel878/sockets/sockaddr_inman.html and http://www.ccplusplus.com/2011/10/struct-sockaddrin.html

Diagrams to look smart: https://users.cs.fiu.edu/~czhang/teaching/cen4500/slides/TCP.pdf

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
- limit client body size
setup routes with one or more of the following rules:
    - Define a list of accepted HTTP methods.
    - Define a HTTP redirection
    - Define a directory or a file from where the file should be searched. Aka define root folder.
    - turn on or off directory listing.
    - set a default file to answer if the request is a directory.
    - Execute CGI based on a certain file extension.
    - make it work with POST / GET method.
    - Make the route able to accept uploaded files, and configure where they should be saved.
