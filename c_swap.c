/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   c_swap.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akoykka <akoykka@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/14 08:05:12 by akoykka           #+#    #+#             */
/*   Updated: 2022/08/14 08:07:37 by akoykka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker.h"

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
