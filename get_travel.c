/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_travel.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akoykka <akoykka@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/13 17:17:37 by akoykka           #+#    #+#             */
/*   Updated: 2022/08/13 17:18:48 by akoykka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	is_biggest(t_sort *sort, int value)
{
	t_llist	*temp;

	temp = sort->stack_b;
	while (temp)
	{
		if (temp->content > value)
			return (0);
		temp = temp->next;
	}
	return (1);
}

int	is_smallest(t_sort *sort, int value)
{
	t_llist	*temp;

	temp = sort->stack_b;
	while (temp)
	{
		if (temp->content < value)
			return (0);
		temp = temp->next;
	}
	return (1);
}

int	convert(int travel, int list_len)
{
	if (travel == 0)
		return (travel);
	return (list_len - travel);
}

void	get_travel_a(t_sort *sort, t_optim *optm, t_llist *target)
{
	int		travel;
	t_llist	*temp;

	travel = 0;
	temp = sort->stack_a;
	while (temp != target)
	{
		++travel;
		temp = temp->next;
	}
	optm->forward_a = travel;
	optm->backward_a = convert(travel, llist_len(sort->stack_a));
}

void	get_travel_b(t_sort *sort, t_optim *optm, int value)
{
	int		travel;
	t_llist	*temp;

	travel = 0;
	temp = sort->stack_b;
	while (temp)
	{
		if (is_biggest(sort, temp->content)
			&& (temp->content < value || is_smallest(sort, value)))
		{
			optm->forward_b = travel;
			optm->backward_b = convert(travel, llist_len(sort->stack_b));
			return ;
		}
		if (temp->next && value < temp->content && value > temp->next->content)
		{
			optm->forward_b = travel + 1;
			optm->backward_b = (llist_len(sort->stack_b) - optm->forward_b);
			return ;
		}
		temp = temp->next;
		++travel;
	}
	optm->forward_b = 0;
	optm->backward_b = 0;
}
