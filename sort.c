/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akoykka <akoykka@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 08:13:20 by akoykka           #+#    #+#             */
/*   Updated: 2022/07/30 23:56:54 by akoykka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int get_travel_a(t_sort *sort, int value, int direction)
{
	int travel_dist;
	t_llist *temp;

	temp = sort->stack_a;
	travel_dist = 0;
	while(temp->content != value)
	{
		++travel_dist;
		temp = temp->next;
	}
	if (direction == BACKWARD && travel_dist > 0)
		return (llist_len(sort->stack_a) - travel_dist);
	return (travel_dist);
}

int distance(t_sort *sort, int travel, int direction)
{
	if (direction == BACKWARD && travel)
		return(llist_len(sort->stack_b) - travel);
	return (travel);
}


int get_travel_b(t_sort *sort, int value, int direction)
{
	int travel_dist;
	t_llist *temp;

	temp = sort->stack_b;
	travel_dist = 0;
	if (llist_len(temp) < 1)
		return(0);
	while(temp)
	{
		if (is_biggest(sort, temp->content)
			&& (temp->content < value || is_smallest(sort, value)))
		{
			return(distance(sort, travel_dist, direction));
		}
		if (value < temp->content
			&& (!temp->next ||  value > temp->next->content))
		{
			return(distance(sort, travel_dist + 1, direction));
		}
		temp = temp->next;
		++travel_dist;
	}
	print_list(sort->stack_b);
	printf("stack_b is above the value is %i\n", value);
	printf("hit and miss value didnt fulfill parameters\n");
	exit(1);
}

void get_next_target(t_sort *sort)
{
	t_optim optimum;
	t_llist *temp;

	temp = sort->stack_a;
	while (temp)
	{
		if (temp->chunk == sort->curr_chunk)
		{
			optimum.forward_a = get_travel_a(sort, temp->content, FORWARD);
			optimum.forward_b = get_travel_b(sort, temp->content, FORWARD);
			optimum.backward_a = get_travel_a(sort, temp->content, BACKWARD);
			optimum.backward_b = get_travel_b(sort, temp->content, BACKWARD);
			compare_results(&optimum, temp->content);
		}
		temp = temp->next;
	}
	sort->curr_target = optimum.best_target;
	sort->direction = optimum.direction;
	sort->a_rotation = optimum.best_a;
	sort->b_rotation = optimum.best_b;
}

int is_curr_chunk_sorted(t_sort *sort)
{
	t_llist *temp;

	temp = sort->stack_a;
	while(temp)
	{
		if (temp->chunk == sort->curr_chunk)
			return (0);
		temp = temp->next;
	}
	return (1);
}

void move_target_to_stack_b(t_sort *sort)
{
	while (sort->a_rotation > 0 && sort->b_rotation > 0)
	{
		rotate_both_stacks(sort, sort->direction);
		--sort->a_rotation;
		--sort->b_rotation;
	}
	while (sort->a_rotation > 0)
	{
		rotate_stack_a(sort, sort->direction);
		if (sort->direction == FORWARD)
			ft_strcat(sort->moves, "ra\n");
		else
			ft_strcat(sort->moves, "rra\n");
		--sort->a_rotation;
	}
	while (sort->b_rotation > 0)
	{
		rotate_stack_b(sort, sort->direction);
		if(sort->direction == FORWARD)
			ft_strcat(sort->moves, "rb\n");
		else
			ft_strcat(sort->moves, "rrb\n");
		--sort->b_rotation;
	}
	push_stack(sort, STACK_A);
}

void align_biggest_number(t_sort *sort)
{
	int big;
	t_llist *temp;
	int steps;
	int direction;

	direction = FORWARD;
	steps = 0;
	temp = sort->stack_b;
	big = temp->content;
	while(temp)
	{
		if (temp->content > big)
			big = temp->content;
		temp = temp->next;
	}
	temp = sort->stack_b;
	while(temp->content != big)
	{
		temp = temp->next;
		++steps;
	}
	if (steps > (int)llist_len(sort->stack_b) / 2 )
	{
		steps = llist_len(sort->stack_b) - steps;
		direction = BACKWARD;
	}
	while (steps--)
	{
		rotate_stack_b(sort, direction);
		ft_strcat(sort->moves, "rb\n");
	}
}

void sort_integers(t_sort *sort)
{

	while(sort->curr_chunk)
	{
		while(!is_curr_chunk_sorted(sort))
		{
			get_next_target(sort);
			move_target_to_stack_b(sort);
		}
		--sort->curr_chunk;
	}
	align_biggest_number(sort);
	while(sort->stack_b)
	{
		push_stack(sort, STACK_B);
	}
}
