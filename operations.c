/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akoykka <akoykka@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/29 11:38:47 by akoykka           #+#    #+#             */
/*   Updated: 2022/07/29 12:09:29 by akoykka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void 	push_stack(t_sort *sort, int stack)
{
	t_llist *target;

	if (stack == STACK_A)
	{
		target = sort->stack_a;
		sort->stack_a = sort->stack_a->next;
		target->next = sort->stack_b;
		sort->stack_b = target;
		ft_strcat(sort->moves, "pa\n");
	}
	if (stack == STACK_B)
	{
		target = sort->stack_b;
		sort->stack_b = sort->stack_b->next;
		target->next = sort->stack_a;
		sort->stack_a = target;
		ft_strcat(sort->moves, "pb\n");
	}
}

void rotate_stack_a(t_sort *sort, int direction)
{
	t_llist *temp;
	t_llist *target;

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
	while(temp->next != target)
		temp = temp->next;
	temp->next = NULL;
	target->next = sort->stack_a;
	sort->stack_a = target;
	}
}

void rotate_stack_b(t_sort *sort, int direction)
{
	t_llist *temp;
	t_llist *target;

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
		while(temp->next != target)
			temp = temp->next;
		temp->next = NULL;
		target->next = sort->stack_b;
		sort->stack_b = target;
	}
}

void rotate_both_stacks(t_sort *sort, int direction)
{
	rotate_stack_a(sort, direction);
	rotate_stack_b(sort, direction);
	if (direction == FORWARD)
		ft_strcat(sort->moves, "rr\n");
	if (direction == BACKWARD)
		ft_strcat(sort->moves, "rrr\n");
}