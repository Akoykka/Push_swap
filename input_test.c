/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_test.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akoykka <akoykka@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/06 11:22:32 by akoykka           #+#    #+#             */
/*   Updated: 2022/08/06 17:44:10 by akoykka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker.h"

int is_only_numbers(char *str)
{	
	if (*str == '-' && ft_strlen(str) > 1)
		++str;
	while (*str)
	{
		if (!ft_isdigit(*str))
		{
			printf("isonlynumbers failed\n");
			return(0);
		}
		++str;
	}
	return(1);
}

int is_bigger_than_max(char *str)
{
	if (ft_isdigit(*str))
	{
		if (ft_strlen(str) > 10)
		{
			printf("bigger than max failed(number was %s)\n ", str);
			return (1);
		}
		if (ft_strlen(str) == 10 
			&& ft_strcmp(str, "2147483647") > 0)
		{
			printf("bigger than max failed(number was %s)\n ", str);
			return (1);
		}
	}
	return (0);
}

int is_smaller_than_min(char *str)
{
	if(*str == '-')
	{
		if (ft_strlen(str) > 11)
		{
			printf("smaller than min failed\n");
			return (1);
		}
		if (ft_strlen(str) == 11
			&& ft_strcmp(str, "-2147483648") > 0)
		{
			printf("smaller than min failed\n");
			return (1);
		}
	}
	return(0);
}

int is_dup(char **numbers, int index, int size)
{
	char *target;

	target = numbers[index];
	++index;
	while (size > index)
	{
		if (ft_strcmp(target, numbers[index]) == 0)
		{
			printf("isdup failed\n");
			return(1);
		}
		++index;
	}
	return (0);
}


int is_valid_input(char **input, int size)
{
	int i;

	i = 0;
	while(size > i)
	{	if (!is_only_numbers(input[i])
			|| is_bigger_than_max(input[i])
			|| is_smaller_than_min(input[i])
			|| is_dup(input, i, size))
			return(0);
		++i;
	}
	return(1);
}

int count_numbers(char **array)
{
	int i;

	i = 0;
	while (array[i])
		++i;
	return(i);
}

void save_move(char **dst, char *next_move)
{
	if (!ft_strcmp (next_move, "pa"))
		ft_strcat(*dst, "0");
	else if (!ft_strcmp (next_move, "pb"))
		ft_strcat(*dst, "1");
	else if (!ft_strcmp (next_move, "sa"))
		ft_strcat(*dst, "2");
	else if (!ft_strcmp (next_move, "sb"))
		ft_strcat(*dst, "3");
	else if (!ft_strcmp (next_move, "ss"))
		ft_strcat(*dst, "23");
	else if (!ft_strcmp (next_move, "ra"))
		ft_strcat(*dst, "4");
	else if (!ft_strcmp (next_move, "rb"))
		ft_strcat(*dst, "5");
	else if (!ft_strcmp (next_move, "rr"))
		ft_strcat(*dst, "45");
	else if (!ft_strcmp (next_move, "rra"))
		ft_strcat(*dst, "6");
	else if (!ft_strcmp (next_move, "rrb"))
		ft_strcat(*dst, "7");
	else if (!ft_strcmp (next_move, "rrr"))
		ft_strcat(*dst, "67");
	else
		ft_strcat(*dst, "8");
}

void parse_moves(char **moves)
{
	char *next_move;
	int ret;

	ret = 1;
	next_move = NULL;
	while (ret > 0)
	{
		ret = get_next_line(0, &next_move);
		if (ret == -1)
		{
			printf("error in get_next_line\n");
			exit (1);
		}
		save_move(moves, next_move);
		free(next_move);
		next_move = NULL;
	}
}

void push_a(t_stacks *stacks)
{

	t_llist *target;

	if (stacks->stack_a)
	{
	target = stacks->stack_a;
	stacks->stack_a = stacks->stack_a->next;
	target->next = stacks->stack_b;
	stacks->stack_b = target;
	}
}

void push_b(t_stacks *stacks)
{

	t_llist *target;

	if (stacks->stack_b)
	{
	target = stacks->stack_b;
	stacks->stack_b = stacks->stack_b->next;
	target->next = stacks->stack_a;
	stacks->stack_a = target;
	}
}

void swap_a(t_stacks *stacks)
{
	t_llist *first;
	t_llist *second;

	if (llist_len(stacks->stack_a) > 1)
	{
		first = stacks->stack_a;
		second = stacks->stack_a->next;
		stacks->stack_a = second;
		first->next = second->next;
		second->next = first;
	}
}

void swap_b(t_stacks *stacks)
{
	t_llist *first;
	t_llist *second;

	if (llist_len(stacks->stack_b) > 1)
	{
		first = stacks->stack_b;
		second = stacks->stack_b->next;
		stacks->stack_a = second;
		first->next = second->next;
		second->next = first;
	}
}

void rotate_a(t_stacks *stacks)
{
	t_llist *target;

	target = NULL;

	if (llist_len(stacks->stack_a) > 1)
	{
	target = stacks->stack_a;
	stacks->stack_a = stacks->stack_a->next;
	get_llist_tail(stacks->stack_a)->next = target;
	target->next = NULL;
	}
}

void rotate_b(t_stacks *stacks)
{
	t_llist *target;

	target = NULL;

	if (llist_len(stacks->stack_b) > 1)
	{
	target = stacks->stack_b;
	stacks->stack_b = stacks->stack_b->next;
	get_llist_tail(stacks->stack_b)->next = target;
	target->next = NULL;
	}
}

void rrotate_a(t_stacks *stacks)
{
	t_llist *target;
	t_llist *temp;

	temp = NULL;
	target = NULL;

	if (llist_len(stacks->stack_a) > 1)
	{
	target = get_llist_tail(stacks->stack_a);
	temp = stacks->stack_a;
	while(temp->next != target)
		temp = temp->next;
	temp->next = NULL;
	target->next = stacks->stack_a;
	stacks->stack_a = target;
	}
}

void rrotate_b(t_stacks *stacks)
{
	t_llist *target;
	t_llist *temp;

	temp = NULL;
	target = NULL;

	if (llist_len(stacks->stack_b) > 1)
	{
	target = get_llist_tail(stacks->stack_b);
	temp = stacks->stack_b;
	while(temp->next != target)
		temp = temp->next;
	temp->next = NULL;
	target->next = stacks->stack_b;
	stacks->stack_b = target;
	}
}

void	apply_moves(t_stacks *stacks, char *moves)
{
	static const t_dispatch_table	dispatch_table[9] = {
		push_a,
		push_b,
		swap_a,
		swap_b,
		rotate_a,
		rotate_b,
		rrotate_a,
		rrotate_b,
		error
	};
	while(*moves)
	{
		dispatch_table[*moves - 0](stacks);
		++moves;
	}
}


int main (int arg_count, char **arg_values)
{
	char **numbers;
	char *moves;
	t_stacks *stacks;
	numbers = NULL;
	t_llist *list;

	int ret = 0;

	arg_count--;
	arg_values++;
	moves = (char *)ft_memalloc(sizeof(char) * 40000);
	if(arg_count == 1)
	{
		numbers = ft_strsplit(*arg_values, ' ');
		if (!is_valid_input(numbers, count_numbers(numbers)))
		{
			printf("invalid input (arg_count 1)");
			exit(1);
		}
	}
	else
	{
		if (!is_valid_input(arg_values, arg_count))
		{
			printf("invalid input (arg_count > 1)");
			exit(1);
		}
	}
	printf("REGGAE OKAY INPUT \n");
	
	parse_moves(&moves);
	apply_moves(list, moves);
	//if(is_in_order(list))
	//	printf("OK\n")
	//else
	//	printf("KO\n")

	return (0);
}