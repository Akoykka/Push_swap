/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   c_push.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akoykka <akoykka@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/14 08:06:21 by akoykka           #+#    #+#             */
/*   Updated: 2022/08/14 17:18:22 by akoykka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker.h"

void	push_a(t_stacks *stacks)
{
	t_llist	*target;

	if (stacks->stack_b)
	{
		target = stacks->stack_b;
		stacks->stack_b = stacks->stack_b->next;
		target->next = stacks->stack_a;
		stacks->stack_a = target;
	}
}

void	push_b(t_stacks *stacks)
{
	t_llist	*target;

	if (stacks->stack_a)
	{
		target = stacks->stack_a;
		stacks->stack_a = stacks->stack_a->next;
		target->next = stacks->stack_b;
		stacks->stack_b = target;
	}
}
