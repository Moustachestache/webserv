# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gbricot <gbricot@student.42perpignan.fr    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/12 09:03:02 by gbricot           #+#    #+#              #
#    Updated: 2024/06/02 14:20:51 by gbricot          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = webserv

CXX = c++

CPPFLAGS = -Wall -Wextra -Werror -std=c++98 -Wshadow -Wno-unused -o3

CPPFLAGS_DEBUG =  -std=c++98 -g -fstandalone-debug

SRC =		source/main.cpp \
			source/parsing.cpp \
			source/debug.cpp \
			source/getMimeType.cpp \
			source/buildHeader.cpp \
			include/Prog/Prog.cpp \
			include/Server/Server.cpp \
			include/HttpHeader/HttpHeader.cpp \
			include/Socket/Socket.cpp \
			include/TcpServer/TcpServer.cpp \
			include/Route/Route.cpp \
			include/Exception/Exception.cpp \
			include/HttpError/HttpError.cpp
			

OBJ = $(SRC:.cpp=.o)

WHITE = "\033[0;37m"
RED = "\033[0;31m"
GREEN = "\033[0;32m"

all: $(NAME)

$(NAME): $(OBJ)
	@$(CXX) $(CPPFLAGS) $(OBJ) -o $(NAME)
	@echo $(GREEN)[$(NAME)] Successfully compilated !$(WHITE)

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
