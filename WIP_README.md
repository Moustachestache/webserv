> [!CAUTION]
> work in progress readme
 # TL;DR
big project
<br />very very interesting, much was learned
<br />found many links, at page bottom
<br />we are very hireable now

![](https://i.imgur.com/IuhbEAr.png)
> Gbricot, Yoshi and Odiachen posing after having finished Webserv. Groovy hot babes!

# <i>introduction</i>
"Webserv" is the penultimate group project for the common core of 42. 
<br />In it you use C++98 to implement an HTTP server that manages POST, GET and DELETE methods, as well as a CGI (common gateway interface) and cookies.

# <i>process</i>
This project isn't difficult but it does require q lot of reading and preparation.
<br />This lead us to a week of research and self reflective questions, after which we managed to output a simplistic roadmap of MVPs with the goal of ushering ourselves forward. The roadmap went as follows:
0. Read up documentation and interview other students on their approach and the pitfalls they encountered.
1. Setup basic sockets you can ping by connecting to 0.0.0.0:8080
2. Add an intelligible HTTP response
3. Send back correct GET request
4. Implement remaining methods (POST and DELETE)
5. Executable python and bash script on server
6. Cookies and sessions? sure let's just hammer them in.

This was not a perfect approach, and we had to go back and some aspects that were too simplistic. Some others were overengineered and should have been scaled down.
</br>For the sake of self reflection and posterity, here here:
| overengineered | too naive |
| ---  | ---  |
| <b>http error as an object</b> with the idea that it would be accessible everywhere.<br />This turned into a great example of an object that could just be a set of functions, because instead we end up creating the HttpError object in different places. |  <b>Receiving the http header into a simple string.</b><br />This was later changed into an HttpHeader object that receives and parses the header, but also the request body (in our case, any POST form request) and creates a vector with all the DATA to be passed to the CGI. |
| im sure there is more | hehe |

# <i>what the code does</i>
| links |  |
| --- | --- |
| https://datatracker.ietf.org/doc/html/rfc2616 | The absolute number 1 ressource. This is the base document defining everything there is to know about HTTP/1.1. |
| https://developer.mozilla.org/en-US/docs/Web/HTTP/Headers | A very easy-to-digest writeup by the mozilla foundation regarding the content of a header.<br />The website also references all the headers that could be used. |
| https://www.rfc-editor.org/rfc/rfc3875.txt | A good reference document regarding the CGI. |
| https://dl.ebooksworld.ir/books/HTTP.The.Definitive.Guide.Brian.Totty.David.Gourley.OReilly.9781565925090.EBooksWorld.ir.pdf | The single greatest piece of reading you can find. The first 5 chapters teach you 80% of what you have to code. |
|  |  |

# <i>knowledge base and links</i>







