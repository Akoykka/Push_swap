/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_sort.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akoykka <akoykka@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/15 13:14:41 by akoykka           #+#    #+#             */
/*   Updated: 2022/08/19 14:11:43 by akoykka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	simple_is_biggest_of(int value, t_llist *list)
{
	while (list)
	{
		if (value < list->content)
			return (0);
		list = list->next;
	}
	return (1);
}

int	simple_get_travel(t_sort *sort)
{
	t_llist	*temp;
	int		travel;
	int		b_head;

	b_head = sort->stack_b->content;
	travel = 0;
	temp = sort->stack_a;
	while (temp->next)
	{
		if (temp->content < b_head && temp->next->content > b_head)
			return (travel + 1);
		if (simple_is_biggest_of(temp->content, sort->stack_a)
			&& (b_head > temp->content || b_head < temp->next->content))
			return (travel + 1);
		++travel;
		temp = temp->next;
	}
	return (0);
}

void	simple_sort_few(t_sort *sort, t_llist *list)
{
	int	loop;
	int	sorted;

	sorted = 0;
	loop = llist_len(list);
	while (loop--)
	{
		if (is_sorted(sort))
			sorted = 1;
		rotate_stack_a(sort, FORWARD);
	}
	if (!sorted)
	{
		swap(sort, STACK_A);
		print_move(SWAP_A, FORWARD);
	}
}

void	simple_push_back_to_a(t_sort *sort, int travel)
{
	int	direction;
	int	loop;

	if (travel && travel > (llist_len(sort->stack_a) / 2))
	{
		loop = llist_len(sort->stack_a) - travel;
		direction = BACKWARD;
	}
	else
	{
		loop = travel;
		direction = FORWARD;
	}
	while (loop--)
	{
		print_move(ROTATE_A, direction);
		rotate_stack_a(sort, direction);
	}
	print_move(PUSH_A, FORWARD);
	push_to_stack(sort, STACK_A);
}

void	simple_sort(t_sort *sort)
{
	int	travel;

	travel = 0;
	while (llist_len(sort->stack_a) > 3)
	{
		push_to_stack(sort, STACK_B);
		print_move(PUSH_B, FORWARD);
	}
	simple_sort_few(sort, sort->stack_a);
	while (sort->stack_b)
	{
		travel = simple_get_travel(sort);
		simple_push_back_to_a(sort, travel);
	}
	simple_align_stack_a(sort);
}
