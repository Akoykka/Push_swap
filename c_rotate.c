/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   c_rotate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akoykka <akoykka@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/13 18:06:18 by akoykka           #+#    #+#             */
/*   Updated: 2022/08/14 08:08:49 by akoykka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker.h"

void rotate_a(t_stacks *stacks)
{
	t_llist *target;

	target = NULL;

	if (llist_len(stacks->stack_a) > 1)
	{
	target = stacks->stack_a;
	stacks->stack_a = stacks->stack_a->next;
	get_llist_tail(stacks->stack_a)->next = target;
	target->next = NULL;
	}
}

void rotate_b(t_stacks *stacks)
{
	t_llist *target;

	target = NULL;

	if (llist_len(stacks->stack_b) > 1)
	{
	target = stacks->stack_b;
	stacks->stack_b = stacks->stack_b->next;
	get_llist_tail(stacks->stack_b)->next = target;
	target->next = NULL;
	}
}

void	rotate_both(t_stacks *stacks)
{
	rotate_a(stacks);
	rotate_b(stacks);
}
