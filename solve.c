/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solve.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akoykka <akoykka@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/23 18:58:08 by akoykka           #+#    #+#             */
/*   Updated: 2022/07/23 21:30:00 by akoykka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int is_in_remove_list(t_llist *remove, int value)
{
	while(remove)
	{
		if (value == remove->content)
			return (1);
		remove = remove->next;
	}
	return 0;
}



void remove_from_unsolved(t_sort *sort, t_llist *remove)
{
	t_llist *temp;
	t_llist *prev;
	//// remove head
	while (sort->unsolved
		&& is_in_remove_list(remove, sort->unsolved->content))
	{
		temp = sort->unsolved;
		sort->unsolved = sort->unsolved->next;
		//free(temp);
		temp = NULL;
	}

	/// remove rest
	if (sort->unsolved)
		temp = sort->unsolved->next;
	prev = sort->unsolved;

	tahan jai en tajuu
	while(temp)
	{
		while (temp && is_in_remove_list(remove, temp->content))
		{
			temp->next = prev->next;
			//free(temp);
			temp = prev->next;
		}
		else
		{	
			if (prev)
				prev = temp
		}
	}
}

size_t llist_len(t_llist *list)
{
	int count;

	count = 0;
	while (list)
	{
		list = list->next;
		++count;
	}
	return (count);
}

int *llist_to_array(t_llist *list, size_t size)
{
	int *array;
	int i;

	i = 0;
	array = (int *)malloc(sizeof(int) * size);
	while (list)
	{
		array[i] = list->content;
		++i;
		list = list->next;
	}
	return(array);
}

t_llist *llist_get_tail(t_llist *list)
{
	while(list->next)
		list = list->next;

	return (list);
}

void fill_under_sort(t_sort *sort)
{
	t_llist *asc;
	t_llist *desc;
	size_t len;

	len = llist_len(sort->unsolved);	
	desc = solve_numbers(llist_to_array(sort->unsolved, len), len, DESCENDING);
	printf("this is desc\n");
	print_list(desc);
	remove_from_unsolved(sort, desc);
	asc = solve_numbers(llist_to_array(sort->unsolved, len), len, ASCENDING);
	printf("this is asc\n");
	print_list(asc);
	remove_from_unsolved(sort, asc);

	
	llist_get_tail(asc)->next = desc;
	sort->under_sort = asc;
}



void solve_final(t_sort *sort)
{
	fill_under_sort(sort);

	printf("this is under_sort\n");
	print_list(sort->under_sort);
	printf("this is unsolved\n");
	print_list(sort->unsolved);
	printf("this is solved\n");
	print_list(sort->solved);

}