
NAME = webserv

CXX = c++

CPPFLAGS = -Wall -Wextra -Werror -std=c++98 -Wshadow -Wno-unused -o3

CPPFLAGS_DEBUG =  -std=c++98 -g

CPPFLAGS_YOSHI = -Wall -Wextra -std=c++98 -g -fstandalone-debug

SRC =		source/main.cpp \
			source/parsing.cpp \
			source/utilsConvert.cpp \
			source/utilsCheck.cpp \
			source/debug.cpp \
			source/getMimeType.cpp \
			source/buildHeader.cpp \
			include/Prog/Prog.cpp \
			include/Server/Server.cpp \
			include/Socket/Socket.cpp \
			include/TcpServer/TcpServer.cpp \
			include/TcpServer/TcpServerGet.cpp \
			include/TcpServer/TcpServerDelete.cpp \
			include/Route/Route.cpp \
			include/Exception/Exception.cpp \
			include/HttpError/HttpError.cpp \
			include/HttpHeader/HttpHeader.cpp \
			include/HttpHeader/HttpHeaderPost.cpp \
			include/Cgi/Cgi.cpp \
			include/Cookies/Cookies.cpp
			

OBJ = $(SRC:.cpp=.o)

WHITE = "\033[0;37m"
RED = "\033[0;31m"
GREEN = "\033[0;32m"

$(NAME): $(OBJ)
	@$(CXX) $(CPPFLAGS) $(OBJ) -o $(NAME)
	@echo $(GREEN)[$(NAME)] Successfully compilated !$(WHITE)

all: $(NAME)

debug:
	$(CXX) $(CPPFLAGS_DEBUG) $(SRC) -o $(NAME)

regular:
	@$(CXX) $(CPPFLAGS) $(SRC) -o $(NAME)

clean:
	@rm -rf $(OBJ)
	@echo $(RED)Objects files deleted$(WHITE)

fclean: clean
	@rm -f $(NAME)
	@echo $(RED)Program deleted$(WHITE)

re: fclean all

yoshi:
	$(CXX) $(CPPFLAGS_YOSHI) $(SRC) -o $(NAME)
