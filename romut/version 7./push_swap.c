/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akoykka <akoykka@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 13:23:00 by akoykka           #+#    #+#             */
/*   Updated: 2022/07/26 15:07:05 by akoykka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

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

t_llist *llist_new(int content, int type)
{
	t_llist *new;

	new = (t_llist *)ft_memalloc(sizeof(t_llist));
	if(!new)
		return NULL;

	new->content = content;
	new->next = NULL;
	new->type = type;
	return(new);
}


void llist_add(t_llist **list, t_llist *new)
{
	new->next = *list;
	*list = new;
}



t_llist *make_list(int *array, int size, int type)
{
	t_llist *head;
	int i;

	head = NULL;
	i = 0;

	while (size > i)
	{
		llist_add(&head, llist_new(array[i], type));
		++i;
	}
	llist_rev(&head);
	return(head);
}


t_llist *llist_dup_except(t_llist *dup, t_llist *except)
{
	t_llist *temp;
	t_llist *new;

	new = NULL;
	temp = NULL;
	while(dup)
	{
		temp = except;
		while (temp && dup->content != temp->content)
			temp = temp->next;
		if (!temp)
			llist_add(&new, llist_new(dup->content, dup->type));
		dup = dup->next;
	}
	llist_rev(&new);
	return (new);
}


t_sort *make_sort_struct(int *array, int size)
{
	t_sort *sort;

	sort = (t_sort *)ft_memalloc(sizeof(t_sort));
	sort->stack_a = make_list(array,size, ASCENDING);
	sort->solved = solve_numbers(array, size, ASCENDING);
	sort->unsolved = llist_dup_except(sort->stack_a, sort->solved);
	return(sort);
}

void count_ra(t_sort *sort, char *str)
{
	char **moves;
	int amount_of_nodes;
	int counter = 0;
	int extra_moves = 0;
	int total_amount = 0;

	amount_of_nodes = llist_len(sort->stack_a);
	moves = ft_strsplit(str, '\n');

	while(*moves)
	{
		counter = 0;
		while (!strcmp(*moves, "ra"))
		{
			++moves;
			++counter;
			++total_amount;
		}	
		if (counter > amount_of_nodes / 2)
		{
			extra_moves += counter - (amount_of_nodes / 2);
			printf("this many rotates %i\n ", counter);
		}
		++moves;
	}
	


	printf("There is total of %i of rotate_a\n", total_amount);
	printf("There is %i extra_moves of rotate \n", extra_moves);
}


int main (int arg_count, char **arg_values)
{
	int		*array;
	t_sort	*sort;

	arg_values += 1;
	arg_count -= 1;

	array = make_int_array(arg_count, arg_values);
	sort = make_sort_struct(array, arg_count);
	solve_final(sort);


	printf("stack_a is:(%zu members)\n", llist_len(sort->stack_a));
	//print_list(sort->stack_a);
	printf("stack_b is:(%zu members)\n", llist_len(sort->stack_b));
	//print_list(sort->stack_b);
	printf("SOLVED (%zu members)\n", llist_len(sort->solved));
	//print_list(sort->solved);
	printf("UNSOLVED (%zu members)\n", llist_len(sort->unsolved));
	//print_list(sort->unsolved);
	count_moves(sort->moves);
	count_ra(sort, sort->moves);
	//printf("%s", sort->moves);
}
	