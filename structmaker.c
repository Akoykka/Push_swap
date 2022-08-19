/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structmaker.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akoykka <akoykka@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/13 17:27:09 by akoykka           #+#    #+#             */
/*   Updated: 2022/08/19 15:29:30 by akoykka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

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

int	getarrlen(char **str)
{
	int	len;

	len = 0;
	while (str[len])
		++len;
	return (len);
}

void	make_list(t_sort *sort, int argc, char **argv)
{
	char	**temp;

	temp = NULL;
	if (argc == 1)
	{
		temp = ft_strsplit(*argv, ' ');
		sort->stack_a = char_array_to_llist(temp, getarrlen(temp));
		free_array(temp);
		temp = NULL;
	}
	else
		sort->stack_a = char_array_to_llist(argv, argc);
	if (!sort->stack_a)
	{
		print_error("Error\n");
		exit(1);
	}
	sort->stack_b = NULL;
}
