/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swapoldie.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akoykka <akoykka@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 11:35:55 by akoykka           #+#    #+#             */
/*   Updated: 2022/06/07 12:01:30 by akoykka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H
# include <stdlib.h>
# include <stdio.h>
# include "libft/includes/libft.h"
# include "libft/ft_printf/ft_printf.h"

typedef struct s_stack
{
	char 	premoves[10000];
	int		*head_a;
	int		size_a;
	char	operations_a[50000];

	int		*head_b;
	int		size_b;
	char	operations_b[50000];
	
	
	int		current_best;
	char	*current_best_cmd[50000];
	
}			t_stack;

// Utils (utils.c)
void	ft_error (void);
int		*char_array_to_int_array(int argc, char **argv);
int 	is_sorted_rev(t_stack *stacks);
int 	is_sorted(t_stack *stacks);
void	ft_print_array(int *array, size_t size);
t_stack	*make_struct(int argc, char **argv);
void 	increase_indexes_by_one(int *stack, size_t len);
void 	shrink_indexes_by_one(int *stack, size_t len);
// Simplify numbers. (simplify.c)
int 	get_index(int base, int *array, int size, int n);
int 	*simplify_numbers (int *array, int size);

// Operations

void	push_to_stack(t_stack *stack, char push_to);
void	swap_top(t_stack *stack, char swap_stack);
void	rotate_up(t_stack *stack, char rotate_stack);
void	bubble_sort(t_stack *stacks);
void	reverse_order_bubble_sort(t_stack *stacks);
void 	split(t_stack* stacks);


#endif