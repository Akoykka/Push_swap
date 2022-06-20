/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akoykka <akoykka@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 11:35:55 by akoykka           #+#    #+#             */
/*   Updated: 2022/06/20 20:29:50 by akoykka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H
# include <stdlib.h>
# include <stdio.h>
# include "libft/includes/libft.h"
# define ASCENDING 1
# define DESCENDING 0

typedef struct s_stack
{
	t_list	*head_a;
	int		size_a;
	char	operations_a[500000];

	t_list	*head_b;
	int		size_b;
	char	operations_b[500000];

}			t_stack;

typedef struct s_mnode
{
	void 	*content;
	size_t	content_size;
	struct	s_mnode **next;
	size_t	next_size;

}			 t_mnode;

// Utils (utils.c)

void	ft_error (void);
void 	print_list(t_list *head);
void	ft_print_array(int *array, size_t size);


//Preparations
t_stack	*make_struct(int argc, char **argv);
t_list 	*make_list(char **array, int size);


/*
// Simplify numbers. (simplify.c)
int 	get_index(int base, int *array, int size, int n);
int 	*simplify_numbers (int *array, int size);
*/
// Operations
void	rotate(t_stack *stacks, char target_stack);
void	swap(t_stack *stacks, char target_stack);
void	push_to(t_stack *stacks, char push_to_stack);

#endif