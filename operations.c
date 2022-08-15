/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akoykka <akoykka@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/13 17:09:35 by akoykka           #+#    #+#             */
/*   Updated: 2022/08/15 19:50:40 by akoykka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	push_to_stack(t_sort *sort, int stack)
{
	t_llist	*target;

	if (stack == STACK_A)
	{
		target = sort->stack_b;
		sort->stack_b = sort->stack_b->next;
		target->next = sort->stack_a;
		sort->stack_a = target;
	}
	if (stack == STACK_B)
	{
		target = sort->stack_a;
		sort->stack_a = sort->stack_a->next;
		target->next = sort->stack_b;
		sort->stack_b = target;
	}
}

void	rotate_stack_a(t_sort *sort, int direction)
{
	t_llist	*temp;
	t_llist	*target;

	temp = NULL;
	target = NULL;
	if (direction == FORWARD && llist_len(sort->stack_a) > 1)
	{
		target = sort->stack_a;
		sort->stack_a = sort->stack_a->next;
		get_llist_tail(sort->stack_a)->next = target;
		target->next = NULL;
	}
	if (direction == BACKWARD && llist_len(sort->stack_a) > 1)
	{
		target = get_llist_tail(sort->stack_a);
		temp = sort->stack_a;
		while (temp->next != target)
			temp = temp->next;
		temp->next = NULL;
		target->next = sort->stack_a;
		sort->stack_a = target;
	}
}

void	rotate_stack_b(t_sort *sort, int direction)
{
	t_llist	*temp;
	t_llist	*target;

	temp = NULL;
	target = NULL;
	if (direction == FORWARD && llist_len(sort->stack_b) > 1)
	{
		target = sort->stack_b;
		sort->stack_b = sort->stack_b->next;
		(get_llist_tail(sort->stack_b))->next = target;
		target->next = NULL;
	}
	if (direction == BACKWARD && llist_len(sort->stack_b) > 1)
	{
		target = get_llist_tail(sort->stack_b);
		temp = sort->stack_b;
		while (temp->next != target)
			temp = temp->next;
		temp->next = NULL;
		target->next = sort->stack_b;
		sort->stack_b = target;
	}
}
void swap(t_sort *sort, int stack_id)
{
	t_llist *first;
	t_llist *second;

	if (stack_id == STACK_A && llist_len(sort->stack_a) > 1)
	{
		first = sort->stack_a;
		second = sort->stack_a->next;
		first->next = second->next;
		second->next = first;
		sort->stack_a = second;
	}
}

void	rotate_both_stacks(t_sort *sort, int direction)
{
	rotate_stack_a(sort, direction);
	rotate_stack_b(sort, direction);
}
