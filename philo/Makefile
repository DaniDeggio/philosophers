# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dde-giov <dde-giov@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/12 19:14:49 by dde-giov          #+#    #+#              #
#    Updated: 2023/10/29 19:43:38 by dde-giov         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

SRC =  philo.c utils.c\

OBJ = ${SRC:.c=.o}

CC = gcc -Wall -Wextra -Werror -g -pthread

.c.o:
	@${CC} -c $< -o ${<:.c=.o}      

all	: $(NAME)

$(NAME) : $(OBJ)
	@$(CC) $(OBJ) -o $(NAME)

clean :
	@rm -f $(OBJ)
	
fclean : clean
	@rm -f $(NAME)
	
re : fclean all

.PHONY: all clean fclean re