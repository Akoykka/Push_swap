#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H
# include <stdlib.h>
# include <stdio.h>
# include "libft/includes/libft.h"
# define STACK_A	4
# define STACK_B	5
# define FORWARD	1
# define BACKWARD	0
# define TOP		6
# define BOT		7

typedef struct s_optim
{
	int forward_a;
	int forward_b;

	int backward_a;
	int backward_b;

	int direction;
	int best_a;
	int best_b;
	int best_target;
}		t_optim;

typedef struct s_llist
{
	int 			content;
	int				chunk;
	struct s_llist	*next;
}			t_llist;

typedef struct s_sort
{
	char	moves[200000];
	t_llist		*stack_a;
	t_llist		*stack_b;
	int			curr_chunk;

	int			direction;
	int			a_rotation;
	int			b_rotation;
	int			curr_target;

}				t_sort;

/// UTILS.c
int 	*make_int_array(int arg_count, char **arg_values);
int 	*ft_invert_int_array(int *array, size_t size);
void	ft_error(void);
int		is_biggest(t_sort *sort, int value);
int 	is_smallest(t_sort *sort, int value);
int		get_bigger(int value, int valuetwo);
t_llist *get_llist_tail(t_llist *list);
int		*make_int_array(int amount, char **array);

/// DEBUG
void 	ft_print_int_array(int *array, size_t size);
void 	print_list(t_llist *list);
void 	print_move_count(char *str);
int		count_moves(char *str);

/// SIMPLIFY
int 	*simplify_numbers (int *array, int size);

//PUSHSWAP
void 	llist_rev(t_llist **head);
t_llist	*llist_new(int content);
void	llist_add(t_llist **list, t_llist *new);
t_llist	*make_list(int *array, int size, float split);
void	fill_sort_struct(t_sort *sort, int *array, int size, float split);
size_t	llist_len(t_llist *list);

// OPERATIONS.c

void 	push_stack(t_sort *sort, int stack);
void	rotate_stack_a(t_sort *sort, int direction);
void	rotate_stack_b(t_sort *sort, int direction);
void	rotate_both_stacks(t_sort *sort, int direction);

///SORT.C
void	sort_integers(t_sort *sort);
void	align_biggest_number(t_sort *sort);
void	move_target_to_stack_b(t_sort *sort);
int		is_curr_chunk_sorted(t_sort *sort);
void	get_next_target(t_sort *sort);

///get_travel.c
int		get_travel_b(t_sort *sort, int value, int direction);
int		get_travel_a(t_sort *sort, int value, int direction);

//// compare.c
void	compare_results(t_optim *optimum, int target_value);
#endif