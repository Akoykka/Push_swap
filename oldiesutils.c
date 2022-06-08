/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akoykka <akoykka@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/05 20:38:03 by akoykka           #+#    #+#             */
/*   Updated: 2022/06/07 10:49:31 by akoykka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	ft_error(void)
{
	ft_putstr("Error\n");
	exit(1);
}

int is_sorted(t_stack *stacks)
{
	int	i;
	int	loop;

	i = 0;
	loop = stacks->size_a - 1;
	while (loop--)
	{
		if ((stacks->array_a)[i] > (stacks->array_a)[i + 1])
			return (0);
		++i;
	}
	return (1);
}

int is_sorted_rev(t_stack *stacks)
{
	int	i;
	int	loop;

	i = 0;
	loop = stacks->size_b - 1;
	while (loop--)
	{
		if ((stacks->array_b)[i] < (stacks->array_b)[i + 1])
			return (0);
		++i;
	}
	return (1);
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

void	ft_print_array(int *array, size_t size)
{
	int i;

	i = 0;
	while (size--)
	{
		ft_printf("%i\n", array[i]);
		++i;
	}

}

void increase_indexes_by_one(int *stack, size_t len)
{
	int *dst;
	int *src;

	src = stack;
	dst = &stack[1];
	ft_memmove(dst, src,len);
	dst[len] = 0;
}

void shrink_indexes_by_one(int *stack, size_t len)
{

	int *dst;
	int *src;
	
	dst = stack;
	src = &stack[1];
	len -= 2;
	ft_printf("len is %u\n", len);
	ft_memmove(dst, src, (len));

	
}