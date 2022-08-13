/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   align_stack_b.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akoykka <akoykka@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/13 17:22:10 by akoykka           #+#    #+#             */
/*   Updated: 2022/08/13 17:22:39 by akoykka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	get_big(t_llist *list)
{
	int	big;

	big = list->content;
	while (list)
	{
		if (big < list->content)
			big = list->content;
		list = list->next;
	}
	return (big);
}

int	get_dist_to_big(t_llist *list, int big)
{
	int	distance;

	distance = 0;
	while (list && list->content != big)
	{
		distance++;
		list = list->next;
	}
	return (distance);
}

void	align_stack_b(t_sort *sort)
{
	int	distance;
	int	direction;

	direction = FORWARD;
	distance = get_dist_to_big(sort->stack_b, get_big(sort->stack_b));
	if (distance > (llist_len(sort->stack_b) / 2))
	{
		distance = llist_len(sort->stack_b) - distance;
		direction = BACKWARD;
	}
	while (distance)
	{
		rotate_stack_b(sort, direction);
		add_move(sort, ROTATE_B, direction);
		--distance;
	}
}
