
#pragma once

# define	NB_SERVER_KW	6

static const char *SERVER_KW[] = {	"SERVER_NAME", \
									"ROOT", \
									"REQUEST_SIZE", \
									"ROUTE", \
									"ERROR_STATUS", \
									"ERROR_LOG"	};

# define NB_ROUTE_KW	9

static const char *ROUTE_KW[] = {	"PATH", \
									"METHOD", \
									"REDIRECTION", \
									"LISTING", \
									"DEFAULT", \
									"ALLOW_UPLOAD", \
									"UPLOAD_PATH", \
									"SESSION_TIMEOUT", \
									"CGI"	};
