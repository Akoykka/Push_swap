/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_move_one_to_tail.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akoykka <akoykka@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 16:42:05 by akoykka           #+#    #+#             */
/*   Updated: 2022/06/07 16:42:31 by akoykka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

void ft_lst_move_one_to_tail(t_list **head, t_list *target)
{
	t_list	*temp;

	temp = *head;
	if (*head == target)
		*head = temp->next;
	else
	{
		while(temp->next != target && temp->next)
			temp = temp->next;
		temp->next = target->next;
	}
	(ft_lst_get_tail(*head))->next = target;
	target->next = NULL;
}
