# webserv
## a C++98 standard http server

# TODO

[les nous du futur]
- [ ] Server &ptrServer into _ptrServer;
- [ ] formes canonique svp quelquun
- [x] Check memory errors (Conditional jumps) in HttpHeader.
- [x] Implement CGI arguments as env in the execve. >> done as ARGV
- [x] Socket.cpp line 15: recode the inet_addr(), unavalible in the subject.
- [ ] retrieve correct upload path for post files
- [ ] (see above) create folders when checking upload paths.
- [ ] add upload size verification
- [x] Implement a check for allow listing, when accessing route.


[MAX]
- [x] how to get a good, clean, scalable buffer for request reception?
- [x] refactor Errorinfo array creation / init
- [x] implement "inet_addr()" and "ntohs()" as our own functions
- [x] why double-up message in answer message?
- [x] change all "\n" in http headers to "\r\n" when newline?
- [x] refactor httheader build function from object to single function.
- [x] create meaningful socket / connection.
- [x] How do we handle closing server? graceful? hard stop? how to be sure there are no leaks?
- [x] what to do with the keepalive / persistent connection header?
- [x] setup full docroot path at parsing -- for safety: refuse /../ or /./ or ./ etc. only a folder othewise error
- [x] create folder render if no default index exists. ie access folder and it shows html page with the files in folder
- [x] re-build httpheader object that parses incoming header
- [x] add Allow header to response whiich lists allowed ehaders
- [x] add error 411 see httpHeader object
- [ ] if it crashes in the header initialisation its the math at line 52 -> 58 but if it dont disregard
      
easy todo
- [x] make server send back info
- [x] make server answer any GET request
- [x] process other requests
      
from HTTP The definitive guide by Oreilly:
- [x] 1. Set up connection—accept a client connection, or close if the client is unwanted.
- [x] 2. Receive request—read an HTTP request message from the network.
- [x] 3. Process request—interpret the request message and take action.
- [x] 4. Access resource—access the resource specified in the message.
- [x] 5. Construct response—create the HTTP response message with the right headers.
- [x] 6. Send response—send the response back to the client.
- [x] 7. Log transaction—place notes about the completed transaction in a log file.

[GREG]
- [x] decide in team the default values for each unset variable (see Server and Route constructors)
- [x] Implement a check function after the parsing
# DOING

##	Exploratory Qs
what does a default .conf look like? what do we expect from it?

hows an HTTP request built. how do we process it?

what path does data take from A to Z.

how is data uploaded? how do you send a form?

where does CGI fit into this? what even is it?

why do we use select() or poll()?

Pipelining? What is it? why? Do we need to implement it?

who is EOF

what is chunked request? How to unchunk?

##	RFC / Documentation
HTTP:            https://datatracker.ietf.org/doc/html/rfc2616

HTTP Headers:	https://developer.mozilla.org/en-US/docs/Web/HTTP/Headers

HTTP response headers:	https://developer.mozilla.org/en-US/docs/Web/HTTP/Messages#http_responses

HTTP Multiform/data upload:      https://www.rfc-editor.org/rfc/rfc7578

HTTP/1.1 reference:	https://datatracker.ietf.org/doc/html/rfc9112

HTTP caching (2022):	https://datatracker.ietf.org/doc/html/rfc9111

HTTP Message Syntax and Routing (2024): https://datatracker.ietf.org/doc/html/rfc6585

Additional HTTP status codes: https://datatracker.ietf.org/doc/html/rfc6585

CGI specification document: https://www.rfc-editor.org/info/rfc3875

##	links
the bible:           https://dl.ebooksworld.ir/books/HTTP.The.Definitive.Guide.Brian.Totty.David.Gourley.OReilly.9781565925090.EBooksWorld.ir.pdf

C++ http server writeup:    https://osasazamegbe.medium.com/showing-building-an-http-server-from-scratch-in-c-2da7c0db6cb7
-> regarding sockaddr_in:   https://www.gta.ufrj.br/ensino/eel878/sockets/sockaddr_inman.html and http://www.ccplusplus.com/2011/10/struct-sockaddrin.html

Sockets (Juliusz Chroboczek, Universite Paris Diderot):    https://www.pps.jussieu.fr/~jch/enseignement/sockets.pdf

regarding select():    https://www.lowtek.com/sockets/select.html

http:    https://developer.mozilla.org/en-US/docs/Web/HTTP/Overview

Diagrams to look smart: https://users.cs.fiu.edu/~czhang/teaching/cen4500/slides/TCP.pdf

CGI on Wikipedia: https://en.wikipedia.org/wiki/Common_Gateway_Interface

More on CGI:    http://www.mnuwer.dbasedeveloper.co.uk/dlearn/web/session01.htm

NGINX default .conf:    https://www.nginx.com/resources/wiki/start/topics/examples/full/

apache server Documentation:    https://httpd.apache.org/docs/current/

some video  on cgi: https://www.youtube.com/watch?v=sSy5EdRd7zc&ab_channel=Homedeve

some other video: https://www.youtube.com/watch?v=eFCiNdY8CS4&ab_channel=ControllersTech

get and post: https://www.ionos.fr/digitalguide/sites-internet/developpement-web/get-vs-post/

practical to fetch mime types:      https://mimetype.io/all-types

regardeing CGI variables:      https://www6.uniovi.es/~antonio/ncsa_httpd/cgi/env.html

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
