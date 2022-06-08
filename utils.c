/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akoykka <akoykka@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 17:08:48 by akoykka           #+#    #+#             */
/*   Updated: 2022/06/07 20:44:35 by akoykka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	ft_error(void)
{
	ft_putstr("Error\n");
	exit(1);
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

void print_list(t_list *head)
{
	t_list *temp;
	int value;

	temp = head;
	while (temp != NULL)
	{
	value = *((int *)temp->content);
	ft_printf("%i \n", value);
	temp = temp->next;
	}
}