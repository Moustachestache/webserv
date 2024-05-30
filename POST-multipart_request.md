[DEBUG] Custom error page added : id=100 - path=PATH_TO_FILE
Parsing OK
server[127.0.0.1:9090]
{
	SERVER_NAME = localhost
	CONTACT = postmaster@localhost
	ROOT = www/
	MAX_HEADER_SIZE = 8192
	REQUEST_SIZE = 128

	ROUTE[/]
	{
		METHOD = GET POST DELETE
		REDIRECTION = 
		LISTING = forbid
		DEFAULT =
		ALLOW_UPLOAD = allow
		UPLOAD_PATH = pickle
		SESSION_TIMEOUT = 600

		CGI[bash]
		{
			PATH = /bin/sh
			EXTENSION =  .sh .bash
		}
	}


	ROUTE[/]
	{
		METHOD = GET POST DELETE
		REDIRECTION = static_website/website/very/far/away/
		LISTING = forbid
		DEFAULT =
		ALLOW_UPLOAD = allow
		UPLOAD_PATH = upload/
		SESSION_TIMEOUT = 600

		CGI[bash]
		{
			PATH = /bin/sh
			EXTENSION =  .sh .bash
		}
	}

	MAX_CONNECTIONS = 48
	ERROR_LOG = log/errorlog.txt
}
Starting server: localhost at 127.0.0.1 on port 9090
POST / HTTP/1.1
Host: 127.0.0.1:9090
User-Agent: curl/7.81.0
Accept: application/json
Authorization: Bearer *********************
Cookie: staging-connections-canary="45412ba154f512d34"
Content-Length: 338
Content-Type: multipart/form-data; boundary=------------------------bcc2cc6e692c067c

--------------------------bcc2cc6e692c067c
Content-Disposition: form-data; name="options"

{"options":{},"url":"https://test.url.com","sslVersion":"TLS 1.2","password":xxxxxxxxxx,"userId":xxxxxxxxxx,"displayName":"Pedro","jobName":"pedro_test_job","batchsize":1000,"waitTimeoutms":10000}
--------------------------bcc2cc6e692c067c--

/
Full path:www/
ServerAnswerLs()
Path :
.html
text/html

