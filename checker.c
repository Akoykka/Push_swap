/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akoykka <akoykka@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/08 14:02:00 by akoykka           #+#    #+#             */
/*   Updated: 2022/08/16 16:34:50 by akoykka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker.h"

void	error_n_exit(t_stacks *stacks)
{
	write(2, "Error\n", 6);
	llist_destroy(&stacks->stack_a);
	llist_destroy(&stacks->stack_b);
	llist_destroy(&stacks->moves);
	exit (1);
}

int	parse_move(char *next_move)
{
	if (!ft_strcmp (next_move, "pa"))
		return (0);
	if (!ft_strcmp (next_move, "pb"))
		return (1);
	if (!ft_strcmp (next_move, "sa"))
		return (2);
	if (!ft_strcmp (next_move, "sb"))
		return (3);
	if (!ft_strcmp (next_move, "ss"))
		return (4);
	if (!ft_strcmp (next_move, "ra"))
		return (5);
	if (!ft_strcmp (next_move, "rb"))
		return (6);
	if (!ft_strcmp (next_move, "rr"))
		return (7);
	if (!ft_strcmp (next_move, "rra"))
		return (8);
	if (!ft_strcmp (next_move, "rrb"))
		return (9);
	if (!ft_strcmp (next_move, "rrr"))
		return (10);
	return (11);
}

void	get_moves(t_stacks *stacks)
{
	char	*next_move;
	int		ret;
	t_llist	*new;

	next_move = NULL;
	ret = get_next_line(0, &next_move);
	while (ret)
	{
		if (ret == -1)
			error_n_exit(stacks);
		new = llist_new(parse_move(next_move));
		if (!new)
		{
			free(next_move);
			error_n_exit(stacks);
		}
		llist_add(&stacks->moves, new);
		free(next_move);
		next_move = NULL;
		ret = get_next_line(0, &next_move);
	}
	llist_rev(&stacks->moves);
}

void	execute_moves(t_stacks *stacks)
{
	int								i;
	t_llist							*temp;
	static const t_dispatch_table	dispatch_table[12] = {
		push_a,
		push_b,
		swap_a,
		swap_b,
		swap_both,
		rotate_a,
		rotate_b,
		rotate_both,
		rrotate_a,
		rrotate_b,
		rrotate_both,
		error_n_exit
	};

	temp = stacks->moves;
	i = 0;
	while (temp)
	{
		dispatch_table[temp->content](stacks);
		temp = temp->next;
	}
}

int	main(int arg_count, char **arg_values)
{
	t_stacks	stacks;

	arg_count--;
	arg_values++;
	make_struct(arg_count, arg_values, &stacks);
	get_moves(&stacks);
	execute_moves(&stacks);
	if (is_in_order(&stacks))
		write(1, "OK\n", 3);
	else
		write(1, "KO\n", 3);
	free_all(&stacks);
	return (0);
}
