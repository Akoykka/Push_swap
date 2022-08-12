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
# define PUSH_A		10
# define PUSH_B		11
# define ROTATE_A	12
# define RROTATE_A	13
# define ROTATE_B	14
# define RROTATE_B  15
# define ROTATE_BOTH 16
# define RROTATE_BOTH 17

typedef struct s_optim
{
	int forward_a;
	int backward_a;
	int forward_b;
	int backward_b;
	int value;

	int least_moves;
	int a_direction;
	int best_a;
	int b_direction;
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
	t_llist		*moves;
	t_llist		*stack_a;
	t_llist		*stack_b;
	t_llist		*current_best;

	float		split;
	float		max_split;

	int			a_direction;
	int			a_rotation;
	int			b_direction;
	int			b_rotation;
	int			curr_target;

}				t_sort;

//OPERATIONS
void 	push_stack(t_sort *sort, int stack);
void 	rotate_stack_a(t_sort *sort, int direction);
void 	rotate_stack_b(t_sort *sort, int direction);
void 	rotate_both_stacks(t_sort *sort, int direction);

//VALIDATOR
int is_only_numbers(char *str);
int is_bigger_than_max(char *str);
int is_smaller_than_min(char *str);
int is_dup(char **numbers, int index, int size);
int is_valid_input(char **input, int size);

/// UTILS ??
int		 getarrlen(char **str);
t_llist	*char_array_to_llist(char **array, int size);
float adjust_split(void);

/// ASSIGN CHUNKS

t_llist *find_smallest(t_llist *list);
t_llist *find_next_smallest(t_llist *list, int prev_value);
int 	assign(t_sort *sort, int n);
void 	assign_chunks(t_sort *sort);

/// STRUCT MAKER

void make_struct(t_sort *sort, int argc, char **argv);

/// GET TARGET

int get_travel_a(t_sort *sort, t_llist *target);
int distance(t_sort *sort, int travel, int direction);
int get_travel_b(t_sort *sort, int value);
void get_next_target(t_sort *sort, int current_chunk);


/// COMPARE

void compare_both_forward(t_optim *optm);
void compare_both_backward(t_optim *optm);
void compare_forward_a_backward_b(t_optim *optm);
void compare_forward_b_backward_a(t_optim *optm);
void compare_results(t_optim *optm);

/// LLIST FUNCTIONS
t_llist	*get_llist_tail(t_llist *list);
t_llist *llist_new(int content);
size_t	llist_len(t_llist *list);
void	llist_add_tail(t_llist *head, t_llist *new); //onestar here might be bug
void	llist_destroy(t_llist **list);
void 	llist_rev(t_llist **head);
void	llist_add(t_llist **list, t_llist *new);



/// OPERATIONS ROTATE & PUSH
void 	push_stack(t_sort *sort, int stack);
void 	rotate_stack_a(t_sort *sort, int direction);
void 	rotate_stack_b(t_sort *sort, int direction);
void 	rotate_both_stacks(t_sort *sort, int direction);
void 	add_move(t_sort *sort, int move_id, int direction);

/// SORT
void move_target_to_stack_b(t_sort *sort);
int is_curr_chunk_sorted(t_sort *sort, int curr_chunk);
void sort_integers(t_sort *sort);
void compare_sort(t_sort *sort);

///ALIGN BIG
int get_big(t_llist *list);
int get_dist_to_big(t_llist *list, int big);
void align_biggest_number(t_sort *sort);

#endif