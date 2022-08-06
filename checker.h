#ifndef CHECKER_H
# define CHECKER_H
# include <stdlib.h>
# include <stdio.h>
# include "libft/includes/libft.h"
# include "libft/includes/get_next_line.h"
# define STACK_A	4
# define STACK_B	5
# define FORWARD	1
# define BACKWARD	0
# define TOP		6
# define BOT		7

typedef struct s_llist
{
	int 			content;
	int				chunk;
	struct s_llist	*next;
}			t_llist;

typedef struct s_stacks
{
	t_llist		*stack_a;
	t_llist		*stack_b;
}			t_stacks;

#endif