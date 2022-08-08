/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_test.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akoykka <akoykka@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/06 11:22:32 by akoykka           #+#    #+#             */
/*   Updated: 2022/08/08 14:00:03 by akoykka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker.h"

int	*char_array_to_int_array(int amount, char **array)
{
	int	*stack;
	int	i;

	i = 0;
	stack = (int *)ft_memalloc(sizeof(int) * (amount));
	while (amount > i)
	{
		stack[i] = ft_atoi(array[i]);
		++i;
	}
	return (stack);
}

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
	while (ret)
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
void is_error(t_stacks *stacks)
{
	printf("error in parsing (moves code 8)");
	exit(1);

}
void	apply_moves(t_stacks *stacks)
{
	int i;

	i = 0;
	static const t_dispatch_table dispatch_table[9] = {
		push_a,
		push_b,
		swap_a,
		swap_b,
		rotate_a,
		rotate_b,
		rrotate_a,
		rrotate_b,
		is_error
	};
	while(stacks->moves[i])
	{
		dispatch_table[stacks->moves[i] - 0](stacks);
		++i;
	}
}
int is_in_order(t_stacks *stacks)
{
	t_llist *temp;

	temp = stacks->stack_a;
	if(stacks->stack_b == NULL)
	{
		while(temp->next)
		{
			if(temp->content > temp->next->content)
				return(0);
			temp = temp->next;
		}
		return(1);
	}
	return(0);
}

void prepare_struct(t_llist **stacks)

int main (int arg_count, char **arg_values)
{
	t_stacks *stacks;
	int		*array;

	arg_count--;
	arg_values++;

	if (arg_count == 1)
	{
		stacks->numbers = ft_strsplit(*arg_values, ' ');
		stacks->size = count_numbers(numbers);
	}
	else
	{
		stacks->numbers = cpy_arg_values(arg_count, arg_values);
		stacks->size = arg_count;
	}
	if (!is_valid_input(stacks->numbers, stacks->size))
		{
			printf("invalid input (arg_count > 1)");
			exit(1);
		}
	array = char_array_to_int_array(arg_count, numbers);
	stacks->stack_a = make_llist(array, arg_count, 0);
	printf("INPUT IS REGGAE OKAY \n");
	parse_moves(&stacks->moves);
	apply_moves(stacks);
	if (is_in_order(stacks))
		printf("OK\n")
	else
		printf("KO\n")
	return (0);
}




yks argumentti:
splitti


useampi argumentti
numerocheck
is number valid

