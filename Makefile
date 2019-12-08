# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yjouaoud <yjouaoud@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/11/01 11:18:43 by jbouazao          #+#    #+#              #
#    Updated: 2019/12/04 17:54:46 by yjouaoud         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = lem-in
FLAGS = -Wall -Werror -Wextra
FILE_NAMES =	lemin.c\
				get_next_line.c\
				f_init.c\
				rooms_list.c\
				ft_misc.c
OBJ = $(FILE_NAMES:.c=.o)
PRINTF_LIBFT = ./ft_printf
LIB = ./ft_printf/libftprintf.a

all: $(NAME)

$(NAME): $(OBJ)
	make -C $(PRINTF_LIBFT)
	gcc -o $(NAME) $(FLAGS) $(OBJ) $(LIB)

clean:
	make clean -C $(PRINTF_LIBFT)
	rm -rf $(OBJ)

fclean: clean
	make fclean -C $(PRINTF_LIBFT)
	rm -rf $(NAME)

re: fclean all