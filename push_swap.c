/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akoykka <akoykka@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 13:23:00 by akoykka           #+#    #+#             */
/*   Updated: 2022/08/14 21:38:19 by akoykka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	add_move(t_sort *sort, int move_id, int direction)
{
	t_llist	*new;

	new = llist_new(move_id);
	if (!new)
	{
		llist_destroy(&sort->stack_a);
		sort->stack_a = NULL;
		llist_destroy(&sort->stack_b);
		sort->stack_b = NULL;
		llist_destroy(&sort->moves);
		sort->moves = NULL;
		print_error("Error\n");
		exit(1);
	}
	if (direction == BACKWARD)
		new->content += 1;
	llist_add(&sort->moves, new);
}

void	move_target_to_stack_b(t_sort *sort)
{
	while (sort->a_rotation || sort->b_rotation)
	{
		if (sort->a_direction == sort->b_direction
			&& sort->a_rotation && sort->b_rotation)
		{
			rotate_both_stacks(sort, sort->a_direction);
			add_move(sort, ROTATE_BOTH, sort->a_direction);
			sort->a_rotation--;
			sort->b_rotation--;
		}
		else if (sort->a_rotation)
		{
			rotate_stack_a(sort, sort->a_direction);
			add_move(sort, ROTATE_A, sort->a_direction);
			sort->a_rotation--;
		}
		else
		{
			rotate_stack_b(sort, sort->b_direction);
			add_move(sort, ROTATE_B, sort->b_direction);
			sort->b_rotation--;
		}
	}
	push_to_stack(sort, STACK_B);
	add_move(sort, PUSH_B, FORWARD);
}

void	get_next_target(t_sort *sort)
{
	t_optim	optm;
	t_llist	*temp;

	temp = sort->stack_a;
	ft_memset(&optm, 0, sizeof(t_optim));
	optm.move_cost = 999999;
	while (temp)
	{	
		get_travel_a(sort, &optm, temp);
		get_travel_b(sort, &optm, temp->content);
		compare_results(&optm, temp->content);
		temp = temp->next;
	}
	sort->curr_target = optm.best_target;
	sort->a_direction = optm.a_direction;
	sort->a_rotation = optm.best_a;
	sort->b_direction = optm.b_direction;
	sort->b_rotation = optm.best_b;
}

void	sort_integers(t_sort *sort)
{
	while (llist_len(sort->stack_a) > 2)
	{
		get_next_target(sort);
		move_target_to_stack_b(sort);
	}
	align_stack_b(sort);
	while (sort->stack_b)
	{
		push_to_stack(sort, STACK_A);
		add_move(sort, PUSH_A, FORWARD);
	}
	llist_rev(&sort->moves);
}

void print_list(t_llist *list)
{
	while (list)
	{
		printf("\t%i\t", list->content);
		list = list->next;
	}
	printf("\n");
}

int	main(int arg_count, char **arg_values)
{
	t_sort	sort;

	arg_count -= 1;
	arg_values += 1;
	make_struct(&sort, arg_count, arg_values);
	if (!is_sorted(&sort))
		sort_integers(&sort);
	print_moves(sort.moves);
	///
	print_list(sort.stack_a);
	///
	free_struct(&sort);
	return (0);
}
