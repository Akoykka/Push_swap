#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H
# include <stdlib.h>
# include <stdio.h>
# include "libft/includes/libft.h"
# define ASCENDING 1
# define DESCENDING 0

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

typedef struct s_sort
{
	char	*moves[50000];
	t_list	*stack_a;
	t_list	*stack_b;

	t_list	*unsolved;
	t_list	*under_sort;
	t_list	*solved;
	int		direction;
}				t_sort;

///Ascending.c

t_list	*solve_numbers(int *array, size_t size);
void 	add_to_tree(t_mnode *mtree, void *content, size_t content_size);
void 	get_insert_point(t_mnode *mtree, t_insert *temp, size_t depth);
int 	move_array_pointer_and_adjust_size(int *array, size_t size);
void 	get_longest_branch(t_mnode *tree, t_branch *branch, size_t depth);

///// Push_swap.c
void print_list(t_list *list);
t_list *int_arr_to_list(int *array, size_t size);
void ft_del(void *target, size_t size);
t_list *remove_extra_from_head(t_list **head, t_list *extra);
int *ft_invert_int_array(int *array, size_t size);
void ft_print_int_array(int *array, size_t size);
int *make_int_array(int arg_count, char **arg_values);
t_sort *make_sort_struct(int *array, size_t size);
#endif