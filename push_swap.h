#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H
# include <stdlib.h>
# include <stdio.h>
# include "libft/includes/libft.h"
# define ASCENDING 	1
# define DESCENDING 0
# define UNSOLVED	2
# define SOLVED		3
# define STACK_A	4
# define STACK_B	5
# define FORWARD	1
# define BACKWARD	0

typedef struct s_llist
{
	int 			content;
	int				type;
	struct s_llist	*next;
}			t_llist;

typedef struct s_solve
{
	size_t		best_depth;
	int 		answer[500];
}			t_solve;

typedef struct s_sort
{
	char	moves[500000000];
	t_llist		*stack_a;
	t_llist		*stack_b;

	t_llist		*solved;
	t_llist 	*under_sort;
	t_llist		*unsolved;
}				t_sort;

typedef struct s_branch
{
	int			current[500];
	
	size_t		answer_depth;
	int 		answer[500];
}			t_branch;

typedef struct s_insert
{
	int			value;
	size_t		max_depth;
	t_mnode 	*insert_point;
}			t_insert;


/// UTILS.c
int 	*make_int_array(int arg_count, char **arg_values);
int 	*ft_invert_int_array(int *array, size_t size);
void	ft_error(void);

/// DEBUG
void 	ft_print_int_array(int *array, size_t size);
void 	print_list(t_llist *list);

//PUSHSWAP
void llist_rev(t_llist **head);
t_llist *llist_new(int content, int type);
void llist_add(t_llist **list, t_llist *new);
t_llist *make_list(int *array, int size, int type);
t_sort *make_sort_struct(int *array, int size);
void 	solve_final(t_sort *sort);

///replace.c

t_llist	*solve_numbers(int *array, size_t size, int sort);
void 	add_to_tree(t_mnode *mtree, void *content, size_t content_size);
void 	get_insert_point(t_mnode *mtree, t_insert *temp, size_t depth);
int 	move_array_pointer_and_adjust_size(int *array, size_t size);
void 	get_longest_branch(t_mnode *tree, t_branch *branch, size_t depth);
t_llist *llist_dup_except(t_llist *dup, t_llist *except);

#endif