# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: deggio <deggio@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/12 19:14:49 by dde-giov          #+#    #+#              #
#    Updated: 2023/11/15 06:32:57 by deggio           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

SRC =  philo.c init.c supervisor.c\
		routine.c utils.c\

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