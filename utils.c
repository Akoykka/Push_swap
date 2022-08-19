/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akoykka <akoykka@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/13 17:24:27 by akoykka           #+#    #+#             */
/*   Updated: 2022/08/19 15:36:24 by akoykka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	free_struct(t_sort *sort)
{
	llist_destroy(&sort->stack_a);
	sort->stack_a = NULL;
	llist_destroy(&sort->stack_b);
	sort->stack_b = NULL;
}

void	print_error(char *str)
{
	write(2, str, ft_strlen(str));
}

void	free_array(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		free(str[i]);
		str[i] = NULL;
		++i;
	}
}

int	is_sorted(t_sort *sort)
{
	t_llist	*temp;

	if (llist_len(sort->stack_a) < 2)
		return (1);
	temp = sort->stack_a;
	while (temp)
	{
		if (temp->next && temp->content > temp->next->content)
			return (0);
		temp = temp->next;
	}
	return (1);
}
