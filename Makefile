# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dde-giov <dde-giov@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/12 19:14:49 by dde-giov          #+#    #+#              #
#    Updated: 2023/10/16 17:59:11 by dde-giov         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC =  philo/philo.c philo/utils.c\

OBJ = ${SRC:.c=.o}
NAME = philo

SRC_B = philo_bonus/philo_bonus.c philo_bonus/utils_bonus.c\
OBJ_B =	${SRC_B:.c=.o}
NAME_B = philo_bonus
OUT = ${filter-out push_swap.o ,${OBJ}}

CC = gcc -Wall -Wextra -Werror -g

.c.o:
	@${CC} -c $< -o ${<:.c=.o}      

all	: $(NAME)

$(NAME) : $(OBJ)
	@$(CC) $(OBJ) -o $(NAME)

bonus : $(NAME) $(OBJ_B)
	@$(CC) $(OUT) $(OBJ_B) -o $(NAME_B)

clean :
	@rm -f $(OBJ)
	@rm -f $(OBJ_B)
	
fclean : clean
	@rm -f $(NAME)
	@rm -f $(NAME_B)
	
re : fclean all bonus

.PHONY: all clean fclean re