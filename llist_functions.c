/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   llist_functions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akoykka <akoykka@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/06 16:28:16 by akoykka           #+#    #+#             */
/*   Updated: 2022/08/12 15:22:52 by akoykka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void llist_destroy(t_llist **list)
{
	t_llist *temp;
	t_llist *next;

	if(!list)
		return ;
	next = NULL;
	temp = *list;

	while(temp)
	{
		next = temp->next;
		free(temp);
		temp = next;
	}
	list = NULL;
}

void llist_rev(t_llist **head)
{
	t_llist	*temp_prevnode;
	t_llist	*temp;
	t_llist	*temp_nextnode;

	temp_prevnode = NULL;
	temp_nextnode = NULL;
	if (!head || !*head)
		return ;
	temp = *head;
	while (temp)
	{
		temp_nextnode = temp->next;
		temp->next = temp_prevnode;
		temp_prevnode = temp;
		temp = temp_nextnode;
	}
	*head = temp_prevnode;
}

t_llist *llist_new(int content)
{
	t_llist *new;

	new = (t_llist *)ft_memalloc(sizeof(t_llist));
	if(!new)
		return NULL;

	new->content = content;
	new->next = NULL;
	new->chunk = 0;
	return(new);
}

void llist_add(t_llist **list, t_llist *new)
{
	new->next = *list;
	*list = new;
}

/*
t_llist *make_list(int *array, int size, float split)
{
	t_llist *head;
	int i;

	head = NULL;
	i = 0;
	while (size > i)
	{
		llist_add(&head, llist_new(array[i]));
		if(!head)
			return NULL;
		head->chunk = assign_chunk(array[i], size, split);
		++i;
	}
	llist_rev(&head);
	return(head);
}
*/

size_t llist_len(t_llist *list)
{
	size_t length;

	length = 0;
	while (list)
	{
		length++;
		list = list->next;
	}
	return (length);
}