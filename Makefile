# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gbricot <gbricot@student.42perpignan.fr    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/12 09:03:02 by gbricot           #+#    #+#              #
#    Updated: 2024/05/12 12:37:26 by gbricot          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = webserv

CC = c++

CPPFLAGS = -Wall -Wextra -Werror -g -std=c++98 -Wshadow -Wno-unused

SRC =		source/main.cpp \
			include/Prog/Prog.cpp \
			include/Server/Server.cpp \
			include/Route/Route.cpp \
			include/HttpError/HttpError.cpp \
			include/Exception/Exception.cpp


OBJ = $(SRC:.cpp=.o)

WHITE = "\033[0;37m"
RED = "\033[0;31m"
GREEN = "\033[0;32m"

all: $(NAME)

$(NAME): $(OBJ)
	@$(CC) $(CPPFLAGS) $(OBJ) -o $(NAME)
	@echo $(GREEN)[$(NAME)] Successfully compilated !$(WHITE)

regular:
	@$(CC) $(CPPFLAGS) $(SRC) -o $(NAME)

clean:
	@rm -rf $(OBJ)
	@echo $(RED)Objects files deleted$(WHITE)

fclean: clean
	@rm -f $(NAME)
	@echo $(RED)Program deleted$(WHITE)

re: fclean all