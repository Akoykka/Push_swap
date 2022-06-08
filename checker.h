/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akoykka <akoykka@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 19:12:28 by akoykka           #+#    #+#             */
/*   Updated: 2022/06/05 18:40:21 by akoykka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHECKER_H
# define CHECKER_H

# include "libft/includes/libft.h"
# include "libft/ft_printf/ft_printf.h"
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# define MAXIM_INT 100000000
# define MINIM_INT -100000000

typedef struct s_stack
{
	int		*array_a;
	size_t	size_a;
	int		*array_b;
	size_t	size_b;
}			t_stack;

int		is_only_numbers(char *str);
int		*char_array_to_int_array(int argc, char **argv);
int		is_valid_input(int argc, char **argv);
int 	is_cmd_valid(char *input);
char	*get_sorting_instructions(void);
void	execute_instructions(t_stack *stacks, char *string);
int		main(int argc, char **argv);

//manipulation
void	rotate_up(t_stack *stack, char stack_id);
void	rrotate_down(t_stack *stack, char stack_id);
void	swap_top(t_stack *stack, char stack_id);
void	push_to_stack(t_stack *stack, char stack_id);
void	operations(t_stack *stack, char *input);

// Check if its in order
void 	is_sorted(t_stack *stacks);

#endif