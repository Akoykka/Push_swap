/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   c_ops.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akoykka <akoykka@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/13 18:06:18 by akoykka           #+#    #+#             */
/*   Updated: 2022/08/13 18:08:21 by akoykka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker.h"

void push_a(t_stacks *stacks)
{

	t_llist *target;

	if (stacks->stack_b)
	{
	target = stacks->stack_b;
	stacks->stack_b = stacks->stack_b->next;
	target->next = stacks->stack_a;
	stacks->stack_a = target;
	}
}

void push_b(t_stacks *stacks)
{

	t_llist *target;

	if (stacks->stack_a)
	{
	target = stacks->stack_a;
	stacks->stack_a = stacks->stack_a->next;
	target->next = stacks->stack_b;
	stacks->stack_b = target;
	}
}



void swap_a(t_stacks *stacks)
{
	t_llist *first;
	t_llist *second;

	if (llist_len(stacks->stack_a) > 1)
	{
		first = stacks->stack_a;
		second = stacks->stack_a->next;
		stacks->stack_a = second;
		first->next = second->next;
		second->next = first;
	}
}

void swap_b(t_stacks *stacks)
{
	t_llist *first;
	t_llist *second;

	if (llist_len(stacks->stack_b) > 1)
	{
		first = stacks->stack_b;
		second = stacks->stack_b->next;
		stacks->stack_b = second;
		first->next = second->next;
		second->next = first;
	}
}

void swap_both(t_stacks *stacks)
{
	swap_a(stacks);
	swap_b(stacks);
}

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