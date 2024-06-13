> [!WARNING]
> work in progress readme

![](https://i.imgur.com/IuhbEAr.png)
> Mjochum, Gbricot and Yoshi posing after having finished Webserv. Groovy hot babes!


1. introduction
2. Process
3. knowledge base and links
4. building blocks and elements
5. challenges
6. general qs to ourselves
7. closing words


# introduction:
"Webserv" is the penultimate group project for the common core of 42. 
In it you use C++98 to implement an HTTP server that manages POST, GET and DELETE methods, as well as a CGI (common gateway interface) and cookies.

# process:
We struggled to approach the project. 
As a group that usually dives in head first, it was daunting. 
We ended up circling back and looking for as much information as possible to build a roadmap, and generate questions for further research.
The roadmap ended up being a series of MVP (minimum viable product) that went as follow:
1. setup basic sockets you can ping by connecting to 0.0.0.0:8080
> Create a socket and uses basic parsing to get the server information.
> Initiate basic dialogue between client and server.
2. add an intelligible HTTP response
> understand HTTP queries and answers.
> initiates basic HTTP parsing in server.
3. send back correct GET request
> understanding METHODS
> finalising good parsing of HTTP requests
> creating of basic ressources (websites and images) to send back.
4. implement remaining methods (POST and DELETE)
> more parsing of POST methods (forms!! AHHHH)
> undertanding the body of a request and when to receive it.
> undertanding safe and unsafe requests.
> setting up the uploading of files and how a file is transferred and saved
5. executable python script on server
> setup of cgi
> how to pass arguments to cgi

# knowledge base and links
This previous month long discovery roadmap helped us raise questions and find ressources. I have linked the ressources as links at the bottom of this readme. Here arem, in short the questions we wrote to ourselves.

> [!NOTE]
> what path does data take from A to Z.what does a default .conf look like? what do we expect from it?
nginx and apache are good examples.
for us it was a matter of walking backwards from what we needed, and translate it into its implementation, following nginx/apache/lighttpd

> [!NOTE]
> hows an HTTP request built. how do we process it?
There is a convention on what an HTTP request is like, and it is all defined in a document that defines most modern HTTP behavior.
The HTTP reauest's HEAD consists of a PHRASE and then HEADERS.
The Phrase has the METHOD followed by the RESSOURCE and the HTTP-VERSION
After a `\r\n` carriage return, we find the HEADERS in the form of `header-name` `:` `value` separated by a colon. ie `content-size: 12345\r\n`
There are more case specific http headers, but that's a problem for future you.

> [!NOTE]
> what path does data take from A to Z.
abstraction layer
we receive a string. we dont have to worry about it. bu you can, checkout tcp packet etc

> [!NOTE]
> how is data uploaded? how do you send a form?
> 

> [!NOTE]
> where does CGI fit into this? what even is it?

> [!NOTE]
> why do we use select() or poll()?

> [!NOTE]
> Pipelinin? What is it? why? Do we need to implement it?

> [!NOTE]
> who is EOF

> [!NOTE]
> what is chunked request? How to unchunk?






