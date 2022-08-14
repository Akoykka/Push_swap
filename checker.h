#ifndef CHECKER_H
# define CHECKER_H
# include <stdlib.h>
# include <stdio.h>
# include "libft/includes/libft.h"
# include "libft/includes/get_next_line.h"



typedef struct s_llist
{
	int 			content;
	struct s_llist	*next;
}			t_llist;

typedef struct s_stacks
{
	t_llist		*stack_a;
	t_llist		*stack_b;
	t_llist		*moves;
}			t_stacks;

typedef void	(*t_dispatch_table)(t_stacks *stacks);
void llist_add(t_llist **list, t_llist *new);
void llist_rev(t_llist **head);
t_llist *llist_new(int content);
size_t llist_len(t_llist *list);
void print_list(t_llist *list);
void llist_destroy(t_llist **list);
void free_all(t_stacks *stacks);
void ft_error(t_stacks *stacks);
void	print_error(char *str);

/// VALIDATION
int is_only_numbers(char *str);
int is_bigger_than_max(char *str);
int is_smaller_than_min(char *str);
int is_dup(char **numbers, int index, int size);
int is_valid_input(char **input, int size);

t_llist	*char_array_to_llist(char **array, int size);
int get_len(char **array);
void free_array(char **array);
void make_struct(int arg_count, char **arg_values, t_stacks *stacks);
int parse_move(char *next_move);
void get_moves(t_stacks *stacks);
t_llist *get_llist_tail(t_llist *list);

/// OPERATIONS
void push_a(t_stacks *stacks);
void push_b(t_stacks *stacks);
void swap_a(t_stacks *stacks);
void swap_b(t_stacks *stacks);
void swap_both(t_stacks *stacks);
void rotate_a(t_stacks *stacks);
void rotate_b(t_stacks *stacks);
void rotate_both(t_stacks *stacks);
void rrotate_a(t_stacks *stacks);
void rrotate_b(t_stacks *stacks);
void rrotate_both(t_stacks *stacks);
void is_error(t_stacks *stacks);
int is_in_order(t_stacks *stacks);

void execute_moves(t_stacks *stacks);
#endif