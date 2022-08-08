/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akoykka <akoykka@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 17:08:48 by akoykka           #+#    #+#             */
/*   Updated: 2022/08/06 20:01:44 by akoykka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int *ft_invert_int_array(int *array, size_t size)
{
	size_t	high;
	size_t	low;
	int		temp;

	if (!array || !size)
		return 0;
	high = size - 1;
	low = 0;
	while(high > low)
	{
		temp = array[high];
		array[high] = array[low];
		array[low] = temp;
		--high;
		++low;
	}
	return (array);
}

int *make_int_array(int arg_count, char **arg_values)
{
	int	i;
	int *array;

	i = 0;
	array = (int *)ft_memalloc(sizeof(int) * arg_count);
	if (!array)
		return(NULL);
	while (arg_count > i)
	{
		array[i] = ft_atoi(arg_values[i]);
		++i;
	}
	return(array);
}

void	ft_error(void)
{
	ft_putstr("Error\n");
	exit(1);
}

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

int get_bigger(int value, int valuetwo)
{
	if (value > valuetwo)
		return (value);
	return(valuetwo);
}

int is_biggest(t_sort *sort, int value)
{
	t_llist *temp;

	temp = sort->stack_b;
	while (temp)
	{
		if (temp->content > value)
			return(0);
		temp = temp->next;
	}
	return (1);
}
int is_smallest(t_sort *sort, int value)
{
	t_llist *temp;

	temp = sort->stack_b;
	while (temp)
	{
		if (temp->content < value)
			return(0);
		temp = temp->next;
	}
	return (1);
}

t_llist *get_llist_tail(t_llist *list)
{
	while (list->next)
		list = list->next;
	return list;
}