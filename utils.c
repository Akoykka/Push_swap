/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akoykka <akoykka@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 17:08:48 by akoykka           #+#    #+#             */
/*   Updated: 2022/07/23 15:42:53 by akoykka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void print_list(t_llist *list)
{	
	if (!list)
		printf("EMPTY LIST\n");
	while(list)
	{
		ft_putnbr(list->content);
		printf("\n");
		list = list->next;
	}
}

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

void ft_print_int_array(int *array, size_t size)
{
	size_t i;

	i = 0;
	while (size > i)
	{
		printf("%i\n", *array);
		++array;
		++i;
	}
}

int *make_int_array(int arg_count, char **arg_values)
{
	int	i;
	int *array;

	i = 0;
	array = (int *)ft_memalloc(sizeof(int) * arg_count);
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
