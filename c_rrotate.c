/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   c_rrotate.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akoykka <akoykka@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/14 08:05:15 by akoykka           #+#    #+#             */
/*   Updated: 2022/08/14 17:14:39 by akoykka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker.h"

void	rrotate_a(t_stacks *stacks)
{
	t_llist	*target;
	t_llist	*temp;

	temp = NULL;
	target = NULL;
	if (llist_len(stacks->stack_a) > 1)
	{
		target = get_llist_tail(stacks->stack_a);
		temp = stacks->stack_a;
		while (temp->next != target)
			temp = temp->next;
		temp->next = NULL;
		target->next = stacks->stack_a;
		stacks->stack_a = target;
	}
}

void	rrotate_b(t_stacks *stacks)
{
	t_llist	*target;
	t_llist	*temp;

	temp = NULL;
	target = NULL;
	if (llist_len(stacks->stack_b) > 1)
	{
		target = get_llist_tail(stacks->stack_b);
		temp = stacks->stack_b;
		while (temp->next != target)
			temp = temp->next;
		temp->next = NULL;
		target->next = stacks->stack_b;
		stacks->stack_b = target;
	}
}

void	rrotate_both(t_stacks *stacks)
{
	rrotate_a(stacks);
	rrotate_b(stacks);
}

void	is_error(t_stacks *stacks)
{
	write(1, "Error, parsing_error\n", 21);
	free_all(stacks);
	exit (1);
}
