/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akoykka <akoykka@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 13:23:00 by akoykka           #+#    #+#             */
/*   Updated: 2022/08/19 15:40:16 by akoykka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	print_move(int move_id, int direction)
{
	if (move_id == ROTATE_A && direction == FORWARD)
		write(1, "ra\n", 3);
	if (move_id == ROTATE_A && direction == BACKWARD)
		write(1, "rra\n", 4);
	if (move_id == ROTATE_B && direction == FORWARD)
		write(1, "rb\n", 3);
	if (move_id == ROTATE_B && direction == BACKWARD)
		write(1, "rrb\n", 4);
	if (move_id == ROTATE_BOTH && direction == FORWARD)
		write(1, "rr\n", 3);
	if (move_id == ROTATE_BOTH && direction == BACKWARD)
		write(1, "rrr\n", 4);
	if (move_id == PUSH_A && direction == FORWARD)
		write(1, "pa\n", 3);
	if (move_id == PUSH_B && direction == FORWARD)
		write(1, "pb\n", 3);
	if (move_id == SWAP_A && direction == FORWARD)
		write(1, "sa\n", 3);
}

void	move_target_to_stack_b(t_sort *sort, t_optim *next_move)
{
	while (next_move->best_a || next_move->best_b)
	{
		if (next_move->a_direction == next_move->b_direction
			&& next_move->best_a && next_move->best_b)
		{
			rotate_both_stacks(sort, next_move->a_direction);
			print_move(ROTATE_BOTH, next_move->a_direction);
			next_move->best_a--;
			next_move->best_b--;
		}
		else if (next_move->best_a)
		{
			rotate_stack_a(sort, next_move->a_direction);
			print_move(ROTATE_A, next_move->a_direction);
			next_move->best_a--;
		}
		else
		{
			rotate_stack_b(sort, next_move->b_direction);
			print_move(ROTATE_B, next_move->b_direction);
			next_move->best_b--;
		}
	}
	push_to_stack(sort, STACK_B);
	print_move(PUSH_B, FORWARD);
}

void	get_next_target(t_sort *sort, t_optim *next_move)
{
	
	t_llist	*temp;

	temp = sort->stack_a;
	ft_memset(next_move, 0, sizeof(t_optim));
	next_move->move_cost = 999999;
	while (temp)
	{
		get_travel_a(sort, next_move, temp);
		get_travel_b(sort, next_move, temp->content);
		compare_results(next_move, temp->content);
		temp = temp->next;
	}
}

void	sort_integers(t_sort *sort)
{
	t_optim	next_move;

	while (sort->stack_a)
	{
		get_next_target(sort, &next_move);
		move_target_to_stack_b(sort, &next_move);
	}
	align_stack_b(sort);
	while (sort->stack_b)
	{
		push_to_stack(sort, STACK_A);
		print_move(PUSH_A, FORWARD);
	}
}

int	main(int arg_count, char **arg_values)
{
	t_sort	sort;

	arg_count -= 1;
	arg_values += 1;
	make_list(&sort, arg_count, arg_values);
	if (!is_sorted(&sort))
	{
		if (llist_len(sort.stack_a) < 11)
			simple_sort(&sort);
		else
			sort_integers(&sort);
	}
	llist_destroy(&sort.stack_a);
	return (0);
}
