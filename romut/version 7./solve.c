/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solve.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akoykka <akoykka@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/23 18:58:08 by akoykka           #+#    #+#             */
/*   Updated: 2022/07/26 14:59:04 by akoykka          ###   ########.fr       */
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

void destroy_list(t_llist **list)
{
	t_llist *free_er;
	if (!list || !*list)
	{
		printf("no list to destroy\n");
		return ;
	}
	while(*list)
	{
		free_er = *list;
		*list = (*list)->next;
		free(free_er);
		free_er = NULL;
	}
	list = NULL;
}


void remove_from_unsolved(t_sort *sort, t_llist *remove)
{
	t_llist *temp;
	t_llist *new_unsolved;

	new_unsolved = NULL;
	temp = sort->unsolved;
	while(temp)
	{
		if (!is_in_remove_list(remove, temp->content))
			llist_add(&new_unsolved, llist_new(temp->content, temp->type));
		temp = temp->next;
	}
	llist_rev(&new_unsolved);
	destroy_list(&sort->unsolved);
	sort->unsolved = new_unsolved;
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

	asc = NULL;
	desc = NULL;
	len = llist_len(sort->unsolved);
	
	if (len == 1)
	{
		sort->under_sort = sort->unsolved;
		sort->unsolved = NULL;
		return ;
	}
	desc = solve_numbers(llist_to_array(sort->unsolved, len), len, DESCENDING);
	
	remove_from_unsolved(sort, desc);
	len = llist_len(sort->unsolved);
	if(sort->unsolved)
	{
		asc = solve_numbers(llist_to_array(sort->unsolved, len), len, ASCENDING);
		remove_from_unsolved(sort, asc);
	}
	llist_get_tail(desc)->next = asc;
	sort->under_sort = desc;
}

int is_stack_a_head_in_under_sort(t_sort *sort)
{
	t_llist *temp;

	if (!sort->stack_a)
		return (0);
	temp = sort->under_sort;
	while (temp)
	{
		if (temp->content == sort->stack_a->content)
		{	
			sort->stack_a->type = temp->type;
			return (1);
		}
		temp = temp->next;
	}
	return (0);
}



void rotate(t_sort *sort, int target)
{
	t_llist *temp;

	temp = NULL;
	if (target == STACK_A && llist_len(sort->stack_a) > 1)
	{
		temp = sort->stack_a;
		(llist_get_tail(temp))->next = temp;
		sort->stack_a = temp->next;
		temp->next = NULL;
		ft_strcat(sort->moves, "ra\n");
	}
	if (target == STACK_B && llist_len(sort->stack_b) > 1)
	{
		temp = sort->stack_b;
		(llist_get_tail(temp))->next = temp;
		sort->stack_b = temp->next;
		temp->next = NULL;
		ft_strcat(sort->moves, "rb\n");
	}
	if (target == SOLVED && llist_len(sort->solved) > 1)
	{
		temp = sort->solved;
		(llist_get_tail(temp))->next = temp;
		sort->solved = temp->next;
		temp->next = NULL;
	}
}

void rrotate(t_sort *sort, int target)
{
	t_llist *temp; 
	t_llist *ptr;

	temp = NULL;
	ptr  = NULL;
	if (target == STACK_B && llist_len(sort->stack_b) > 1)
	{
		ft_strcat(sort->moves, "rrb\n");
		ptr = llist_get_tail(sort->stack_b);
		temp = sort->stack_b;
		while (temp->next != ptr)
			temp = temp->next;
		temp->next = NULL;
		ptr->next = sort->stack_b;
		sort->stack_b = ptr;
	}


}


void push_a_to_b(t_sort *sort)
{
	t_llist *target;

	target = sort->stack_a;

	if (sort->stack_a->type == DESCENDING)
	{
		sort->stack_a = sort->stack_a->next;
		target->next = sort->stack_b;
		sort->stack_b = target;
		ft_strcat(sort->moves, "pa\n");
	}
	else
	{
		sort->stack_a = sort->stack_a->next;
		target->next = sort->stack_b;
		sort->stack_b = target;
		ft_strcat(sort->moves, "pa\n");
		rotate(sort, STACK_B);
	}
}

int is_head_smallest(t_llist *list)
{
	t_llist *temp;

	temp = list;
	while(temp)
	{
		if (list->content > temp->content)
			return (0);
		temp = temp->next;
	}
	return (1);
}

int get_tail_value(t_llist *list)
{
	if(!list)
		printf("no list to get tail value");
	while (list->next)
	{
		list = list->next;
	}
	return(list->content);
}
void move_to_solved(t_sort *sort, int content)
{
	t_llist *temp;
	t_llist *prev;

	prev = sort->under_sort;
	temp = sort->under_sort;

	while(temp->content != content) /// FIND THE NODE
	{
		temp = temp->next;
	}
	if (temp == sort->under_sort) // IS THE HEAD
	{
		sort->under_sort = sort->under_sort->next;
		temp->next = sort->solved;
		sort->solved = temp;
	}
	else // NOT IS THE HEAD
	{
		while (prev->next != temp)
		{
			prev = prev->next;
		}
		prev->next = temp->next;
		temp->next = sort->solved;
		sort->solved = temp;
	}
}

void push_b_to_a(t_sort *sort)
{
	t_llist *target;

	target = sort->stack_b;

	sort->stack_b = sort->stack_b->next;
	target->next = sort->stack_a;
	sort->stack_a = target;
	ft_strcat(sort->moves, "pa\n");
	move_to_solved(sort, sort->stack_a->content);
}

int is_head_b_fit(t_sort *sort)
{
	int head_value;

	head_value = sort->stack_b->content;
	if (head_value > get_tail_value(sort->solved)
		&& head_value < sort->solved->content)
	{
		return(1);
	}
	else if (is_head_smallest(sort->solved)
		&& (head_value > get_tail_value(sort->solved)
		|| head_value < sort->solved->content))
	{
		return(1);
	}
	return(0);
}

int is_tail_b_fit(t_sort *sort)
{
	int tail_value;

	tail_value = get_tail_value(sort->stack_b);

	if (tail_value > get_tail_value(sort->solved)
		&& tail_value < sort->solved->content)
	{
		return(1);
	}
	if (is_head_smallest(sort->solved) 
		&& (tail_value > get_tail_value(sort->solved)
		|| tail_value < sort->solved->content))
	{
		return (1);
	}
	return(0);
}

void rotate_solved(t_sort *sort)
{
	if (sort->stack_a->content == sort->solved->content)
		rotate(sort, SOLVED);
}

void solve_final(t_sort *sort)
{
	while (sort->unsolved || sort->under_sort)
	{
		if (!sort->under_sort && sort->unsolved)
		{
			fill_under_sort(sort);
		}
		if (is_stack_a_head_in_under_sort(sort))
		{
			push_a_to_b(sort);
		}
		else if (sort->stack_b && is_head_b_fit(sort))
		{
			push_b_to_a(sort);
		}
		else if (sort->stack_b && is_tail_b_fit(sort))
		{
			rrotate(sort, STACK_B);
			push_b_to_a(sort);
		}
		else
		{
			rotate_solved(sort);
			rotate(sort, STACK_A);
		}
	}
	/*
	printf("\n------------\n\n");
	printf("this is under_sort\n");
	print_list(sort->under_sort);
	printf("this is unsolved\n");
	print_list(sort->unsolved);
	printf("this is solved\n");
	print_list(sort->solved);
	printf("this is under sort\n");
	print_list(sort->under_sort);
	printf("\n------------\n\n");
	*/
}