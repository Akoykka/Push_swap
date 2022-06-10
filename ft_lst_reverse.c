/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_reverse.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akoykka <akoykka@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 09:09:51 by akoykka           #+#    #+#             */
/*   Updated: 2022/06/09 09:29:42 by akoykka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void ft_lst_reverse(t_list **head)
{
	t_list *temp_prevnode;
	t_list *temp;
	t_list *temp_nextnode;

	if (!head || !*head)
		return;

	temp_prev = NULL;
	temp = *head;
	temp_next = NULL;

	while (temp)
	{
		temp_nextnode = temp->next;
		temp->next = temp_prevnode;
		temp_prevnode = temp;
		temp = temp_nextnode;
	}
	*head = ptr_newnode;
}