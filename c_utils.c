/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   c_utils.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akoykka <akoykka@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/14 08:18:50 by akoykka           #+#    #+#             */
/*   Updated: 2022/08/14 08:27:52 by akoykka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker.h"

void	free_array(char **array)
{
	int	i;

	if (!array)
		return ;
	i = 0;
	while (array[i])
	{
		free(array[i]);
		array[i] = NULL;
		++i;
	}
	free(array[i]);
	free(array);
	array = NULL;
}

int	get_len(char **array)
{
	int	i;

	i = 0;
	while (array[i])
		++i;
	return (i);
}

void	free_all(t_stacks *stacks)
{
	llist_destroy(&(stacks->stack_a));
	llist_destroy(&(stacks->stack_b));
	llist_destroy(&(stacks->moves));
}

void	ft_error(t_stacks *stacks)
{
	write(1, "Error", 6);
	free_all(stacks);
	exit (1);
}

int	is_in_order(t_stacks *stacks)
{
	t_llist	*temp;

	temp = stacks->stack_a;
	if (stacks->stack_b == NULL)
	{
		while (temp->next)
		{
			if (temp->content > temp->next->content)
				return (0);
			temp = temp->next;
		}
		return (1);
	}
	return (0);
}

void	print_error(char *str)
{
	write(2, "str", ft_strlen(str));
}