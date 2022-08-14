/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   c_llist_functions2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akoykka <akoykka@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/13 17:20:39 by akoykka           #+#    #+#             */
/*   Updated: 2022/08/14 08:26:33 by akoykka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker.h"

t_llist	*get_llist_tail(t_llist *list)
{
	t_llist	*temp;

	temp = list;
	if (!temp)
		return (NULL);
	while (temp->next)
		temp = temp->next;
	return (temp);
}

void	llist_add_tail(t_llist *head, t_llist *new)
{
	if (!head)
	{
		head = new;
		return ;
	}
	(get_llist_tail(head))->next = new;
	new->next = NULL;
}
