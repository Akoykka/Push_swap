/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akoykka <akoykka@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 17:08:48 by akoykka           #+#    #+#             */
/*   Updated: 2022/06/17 11:11:03 by akoykka          ###   ########.fr       */
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
		printf("%i\n", array[i]);
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
	printf("%i \n", value);
	temp = temp->next;
	}
}

void push_to(t_stack *stacks, char push_to_stack)
{
	if (push_to_stack == 'a' && stacks->size_b)
	{
		ft_lst_push_top(&(stacks->head_b), &(stacks->head_a));
		++(stacks->size_a);
		--(stacks->size_b);
	}
	if (push_to_stack == 'b' && stacks->size_a)
	{
		ft_lst_push_top(&(stacks->head_a), &(stacks->head_b));
		++(stacks->size_b);
		--(stacks->size_a);
	}
}

void swap(t_stack *stacks, char target_stack)
{
	if (target_stack == 'a' && stacks->size_a > 1)
		ft_lst_move_to_top(&stacks->head_a, (stacks->head_a)->next);
	if (target_stack == 'b' && stacks->size_b > 1)
		ft_lst_move_to_top(&stacks->head_b, (stacks->head_b)->next);
}

void rotate(t_stack *stacks, char target_stack)
{
	if (target_stack == 'a' && stacks->size_a > 1)
		ft_lst_move_one_to_tail(&stacks->head_a, stacks->head_a);
	if (target_stack == 'b' && stacks->size_b > 1)
		ft_lst_move_one_to_tail(&stacks->head_b, stacks->head_b);
}