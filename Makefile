# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: akoykka <akoykka@student.hive.fi>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/13 11:26:04 by akoykka           #+#    #+#              #
#    Updated: 2022/08/16 18:20:42 by akoykka          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = push_swap
NAME_CHECKER = checker

SRC_LIST =	push_swap.c llist_functions.c llist_functions2.c operations.c\
			validator.c compare.c get_travel.c align_stack.c \
			utils.c structmaker.c simple_sort.c

#SRC_LIST += debug.c

SRC_LIST_CHECKER = checker.c c_llist_functions.c c_llist_functions2.c \
					c_push.c c_rotate.c c_rrotate.c c_swap.c c_utils.c \
					c_validator.c c_makestruct.c

OBJECT_LIST = $(SRC_LIST:%.c=%.o)
OBJECT_LIST_CHECKER = $(SRC_LIST_CHECKER:%.c=%.o)

COMPILER = gcc
INCLUDES = -I .
WWW = -Wall -Werror -Wextra
#WWW += -Wconversion
FLAGS = -o
LIB = -lft -L./libft

all: $(NAME) $(NAME_CHECKER)

$(NAME): $(OBJECT_LIST) $(SRC_LIST) Makefile
	make -C libft/
	$(COMPILER) $(WWW) $(OBJECT_LIST) $(INCLUDES) $(FLAGS) $(NAME) $(LIB)

$(NAME_CHECKER): $(OBJECT_LIST_CHECKER) $(SRC_LIST_CHECKER) Makefile
	$(COMPILER) $(WWW) $(OBJECT_LIST_CHECKER) $(INCLUDES) $(FLAGS) $(NAME_CHECKER) $(LIB)

$(OBJECT_LIST_CHECKER): %.o:%.c Makefile
	gcc -c $< $(INCLUDES)

$(OBJECT_LIST): %.o:%.c Makefile
	gcc -c $< $(INCLUDES)

clean:
	@make clean -C libft/
	@rm -f $(OBJECT_LIST)
	@rm -f $(OBJECT_LIST_CHECKER)
	
fclean: clean
	@make fclean -C libft/
	@rm -f $(NAME)
	@rm -f $(NAME_CHECKER)

norm:
	norminette $(SRC_LIST_CHECKER) $(SRC_LIST)

re: fclean all
