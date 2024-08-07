> [!CAUTION]
> THIS SERVER DOES NOT IMPLEMENT RFC 1149 DUE TO LACK OF AVAILABILITY
> <br />**more info**:  https://datatracker.ietf.org/doc/html/rfc1149

![](https://i.imgur.com/IuhbEAr.png)
> Gbricot, Yoshi and Odiachen posing after having finished Webserv. Mjochum not pictured.

# <i>introduction</i>
"Webserv" is the penultimate group project for the common core of 42. 
<br />In it you use C++98 to implement an HTTP server that manages POST, GET and DELETE methods, as well as a CGI (common gateway interface) and cookies.

# <i>process</i>
This project isn't difficult but it does require **a lot** of reading and preparation.
<br />This lead us to a week's worth of research and self reflective questions, after which we managed to output a simplistic roadmap of MVPs with the goal of ushering ourselves forward. The roadmap went as follows:
0. Read up documentation and interview other students on their approach and the pitfalls they encountered.
1. Setup basic sockets you can ping by connecting to 0.0.0.0:8080
2. Add an intelligible HTTP response
3. Send back correct GET request
4. Implement remaining methods (POST and DELETE)
5. Executable python and bash script on server
6. Cookies and sessions? sure let's just hammer them in.

# <i>what the code does</i>
| function | what it do |
| --- | --- |
| Cgi.cpp | Handles executing CGI scripts. Passes the HttpReaquests' variables (http, post, get and files) to the executable program. |
| Httpheader | Receives HttpRequests. Processes it into an object for use later by parsing the incoming message from the client, and then if there is a need parses the body (if POST and Content-Size is relevant).<br />Creates a vector with the header variables to pass to the CGI for the program's argv. |
| Socket | Object that handles the connection information. |
| Prog | Runs the program. High level logic of server. |
| Route | Each defined route is stored here and retreive when needed for redirections. |
| Server<br />& TcpServer | Class and its inherited class. Used to identify each server and have the run independantly. |
| Cookies | Part of TcpServer. Handles cookies. |
| HttpError | Probably the dumbest thing in this code. Mjochum decided early that HttpErrors had to be an object. This allows for storing custom error pages and creating error messages to return to the server. |
| exception | Exception handler. |

# <i>4 links that'll get you there</i>
| links |  |
| --- | --- |
| [Oreilly's definitive guide to HTTP](https://dl.ebooksworld.ir/books/HTTP.The.Definitive.Guide.Brian.Totty.David.Gourley.OReilly.9781565925090.EBooksWorld.ir.pdf) | The single greatest piece of reading you can find. The first 5 chapters teach you 80% of what you have to code.<br />I have come to refer to this book as "the bible". |
| https://datatracker.ietf.org/doc/html/rfc2616 | This is the base document defining everything there is to know about HTTP/1.1.<br />If ever a question pops up, the answer is here. and if it isn't, check again. |
| https://developer.mozilla.org/en-US/docs/Web/HTTP/Headers | A very easy-to-digest writeup by the mozilla foundation regarding the content of a header.<br />The website also references all the headers that could be used. |
| https://www.rfc-editor.org/rfc/rfc3875.txt | A good reference document regarding the CGI. |
# <i>more links</i>
| On connections, select and sending/receiving packets: |
| ---   | 
| C++ http server writeup<br />https://osasazamegbe.medium.com/showing-building-an-http-server-from-scratch-in-c-2da7c0db6cb7 | 
| regarding sockaddr_in<br /> https://www.gta.ufrj.br/ensino/eel878/sockets/sockaddr_inman.html<br />http://www.ccplusplus.com/2011/10/struct-sockaddrin.html | 
| regarding select()<br /> https://www.lowtek.com/sockets/select.html | 
| Sockets (Juliusz Chroboczek, Universite Paris Diderot)<br />https://www.pps.jussieu.fr/~jch/enseignement/sockets.pdf | 

| On the Common Gateway Interface (CGI): |
| ---   | 
| CGI on Wikipedia<br />https://en.wikipedia.org/wiki/Common_Gateway_Interface | 
| More on CGI<br /> http://www.mnuwer.dbasedeveloper.co.uk/dlearn/web/session01.htm | 
| some video on cgi<br />https://www.youtube.com/watch?v=sSy5EdRd7zc&ab_channel=Homedeve | 
| regardeing CGI variables and how to pass them<br />https://www6.uniovi.es/~antonio/ncsa_httpd/cgi/env.html | 

| On the configuration file: |
| ---   | 
| NGINX default .conf<br />https://www.nginx.com/resources/wiki/start/topics/examples/full/ |
| apache server Documentation<br />https://httpd.apache.org/docs/current/ |

| On the Universe, life and everything: |
| ---   | 
| get and post<br />https://www.ionos.fr/digitalguide/sites-internet/developpement-web/get-vs-post/ | 
| practical to fetch mime types<br />https://mimetype.io/all-types | 
| redundant but more on http<br />https://developer.mozilla.org/en-US/docs/Web/HTTP/Overview | 

![](https://i.imgur.com/AJKcUCu.png)
