# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jbouazao <jbouazao@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/11/01 11:18:43 by jbouazao          #+#    #+#              #
#    Updated: 2020/02/16 13:40:05 by jbouazao         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = lem-in
FILE_NAMES =	lemin.c\
				get_next_line.c\
				f_init.c\
				rooms_list.c\
				ft_misc.c\
				ft_queue.c
PRINTF_LIBFT = ./ft_printf
OBJ = $(FILE_NAMES:.c=.o)
FLAGS = -g -Wall -Werror -Wextra

all: $(NAME)

$(NAME): $(OBJ)
	make -C $(PRINTF_LIBFT)
	gcc -o $(NAME) $(FLAGS) $(OBJ) ./ft_printf/libftprintf.a

$(OBJ): %.o:%.c
	gcc -c $(FLAGS) $^ -o $@

clean:
	make clean -C $(PRINTF_LIBFT)
	rm -rf $(OBJ)

fclean: clean
	make fclean -C $(PRINTF_LIBFT)
	rm -rf $(NAME)

re: fclean all