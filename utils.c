/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akoykka <akoykka@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/13 17:24:27 by akoykka           #+#    #+#             */
/*   Updated: 2022/08/14 20:04:13 by akoykka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	free_struct(t_sort *sort)
{
	llist_destroy(&sort->stack_a);
	sort->stack_a = NULL;
	llist_destroy(&sort->stack_b);
	sort->stack_b = NULL;
	llist_destroy(&sort->moves);
	sort->moves = NULL;
}

void	print_error(char *str)
{
	write(2, str, ft_strlen(str));
}

void	free_array(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		free(str[i]);
		str[i] = NULL;
		++i;
	}
}

int	is_sorted(t_sort *sort)
{
	t_llist	*temp;

	if (llist_len(sort->stack_a) < 2)
		return (1);
	temp = sort->stack_a;
	while (temp)
	{
		if (temp->next && temp->content > temp->next->content)
			return (0);
		temp = temp->next;
	}
	return (1);
}

void	print_moves(t_llist *list)
{
	while (list)
	{
		if (list->content == PUSH_A)
			write(1, "pa\n", 3);
		if (list->content == PUSH_B)
			write(1, "pb\n", 3);
		if (list->content == ROTATE_A)
			write(1, "ra\n", 3);
		if (list->content == RROTATE_A)
			write(1, "rra\n", 4);
		if (list->content == ROTATE_B)
			write(1, "rb\n", 3);
		if (list->content == RROTATE_B)
			write(1, "rrb\n", 4);
		if (list->content == ROTATE_BOTH)
			write(1, "rr\n", 3);
		if (list->content == RROTATE_BOTH)
			write(1, "rrr\n", 4);
		list = list->next;
	}
}
