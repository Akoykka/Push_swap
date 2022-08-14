/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   c_makestruct.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akoykka <akoykka@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/14 08:41:40 by akoykka           #+#    #+#             */
/*   Updated: 2022/08/14 08:44:13 by akoykka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker.h"

t_llist	*char_array_to_llist(char **array, int size)
{
	t_llist	*head;
	t_llist	*new;
	int		i;

	head = NULL;
	i = 0;
	if (!is_valid_input(array, size))
		return (NULL);
	while (size > i)
	{
		new = llist_new(ft_atoi(array[i]));
		if (!new)
		{
			llist_destroy(&head);
			return (NULL);
		}
		llist_add(&head, new);
		++i;
	}
	llist_rev(&head);
	return (head);
}

void	make_struct(int arg_count, char **arg_values, t_stacks *stacks)
{
	char	**temp;

	temp = NULL;
	if (arg_count == 1)
	{
		temp = ft_strsplit(*arg_values, ' ');
		stacks->stack_a = char_array_to_llist(temp, get_len(temp));
		free_array(temp);
		temp = NULL;
	}
	else
		stacks->stack_a = char_array_to_llist(arg_values, arg_count);
	if (!stacks->stack_a)
	{
		write(1, "Error\n", 6);
		exit (1);
	}
		stacks->stack_b = NULL;
}
