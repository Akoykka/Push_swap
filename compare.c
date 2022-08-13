/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compare.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akoykka <akoykka@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/13 17:13:57 by akoykka           #+#    #+#             */
/*   Updated: 2022/08/13 17:30:45 by akoykka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	compare_both_forward(t_optim *optm, int value)
{
	int	total_moves;

	if (optm->forward_a > optm->forward_b)
		total_moves = optm->forward_a;
	else
		total_moves = optm->forward_b;
	if (total_moves < optm->move_cost)
	{
		optm->a_direction = FORWARD;
		optm->b_direction = FORWARD;
		optm->best_a = optm->forward_a;
		optm->best_b = optm->forward_b;
		optm->best_target = value;
		optm->move_cost = total_moves;
	}
}

void	compare_both_backward(t_optim *optm, int value)
{
	int	total_moves;

	if (optm->backward_a > optm->backward_b)
		total_moves = optm->backward_a;
	else
		total_moves = optm->backward_b;
	if (total_moves < optm->move_cost)
	{
		optm->a_direction = BACKWARD;
		optm->b_direction = BACKWARD;
		optm->best_a = optm->backward_a;
		optm->best_b = optm->backward_b;
		optm->best_target = value;
		optm->move_cost = total_moves;
	}
}

void	compare_forward_a_backward_b(t_optim *optm, int value)
{
	int	total_moves;

	total_moves = optm->forward_a + optm->backward_b;
	if (total_moves < optm->move_cost)
	{
		optm->a_direction = FORWARD;
		optm->best_a = optm->forward_a;
		optm->b_direction = BACKWARD;
		optm->best_b = optm->backward_b;
		optm->best_target = value;
		optm->move_cost = total_moves;
	}
}

void	compare_forward_b_backward_a(t_optim *optm, int value)
{
	int	total_moves;

	total_moves = optm->forward_b + optm->backward_a;
	if (total_moves < optm->move_cost)
	{
		optm->b_direction = FORWARD;
		optm->best_b = optm->forward_b;
		optm->a_direction = BACKWARD;
		optm->best_a = optm->backward_a;
		optm->best_target = value;
		optm->move_cost = total_moves;
	}
}

void	compare_results(t_optim *optm, int value)
{
	compare_both_forward(optm, value);
	compare_both_backward(optm, value);
	compare_forward_a_backward_b(optm, value);
	compare_forward_b_backward_a(optm, value);
}
