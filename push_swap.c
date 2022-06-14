/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akoykka <akoykka@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 10:09:42 by akoykka           #+#    #+#             */
/*   Updated: 2022/06/14 15:42:06 by akoykka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void push_to(t_stack *stacks, char push_to_stack)
{
	if (push_to_stack == 'a' && stacks->size_b)
	{
		ft_lst_push_top(&(stacks->head_b), &(stacks->head_a));
		++(stacks->size_a);
		--(stacks->size_b);
	}
	if (push_to_stack == 'b' && stacks->size_a)
	{
		ft_lst_push_top(&(stacks->head_a), &(stacks->head_b));
		++(stacks->size_b);
		--(stacks->size_a);
	}
}

void swap(t_stack *stacks, char target_stack)
{
	if (target_stack == 'a' && stacks->size_a > 1)
		ft_lst_move_to_top(&stacks->head_a, (stacks->head_a)->next);
	if (target_stack == 'b' && stacks->size_b > 1)
		ft_lst_move_to_top(&stacks->head_b, (stacks->head_b)->next);
}

void rotate(t_stack *stacks, char target_stack)
{
	if (target_stack == 'a' && stacks->size_a > 1)
		ft_lst_move_one_to_tail(&stacks->head_a, stacks->head_a);
	if (target_stack == 'b' && stacks->size_b > 1)
		ft_lst_move_one_to_tail(&stacks->head_b, stacks->head_b);
}

void ft_lst_reverse(t_list **head)
{
	t_list *temp_prevnode = NULL;
	t_list *temp;
	t_list *temp_nextnode = NULL;

	if (!head || !*head)
		return;
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

	t_list *make_list(char **array, int size)
	{
		t_list *head = NULL;
		t_list *new;
		int number;
		int i;

		i = 0;

		while(i < size)
		{
			number = ft_atoi(array[i]);
			new = ft_lst_new(&number, 4);
			ft_lst_add(&head, new);
			++i;
		}
		ft_lst_reverse(&head);
		return (head);
	}


	t_stack *make_struct(int arg_count, char **argv)
	{
		t_stack *stacks;
		t_list *head_array_a;

		stacks = (t_stack *)ft_memalloc(sizeof(t_stack));
		//if	(arg_count == 1)
		//{
		//	argv = ft_strsplit(*argv, ' ');
		//	stacks->head_a = make_list(argv, arg_count);
		//{
		//else
		stacks->head_a = make_list(argv, arg_count);

		////
		printf("Print list: head_a\n");
		print_list(stacks->head_a);
		printf("Length of list is: %zu\n", ft_lst_count(stacks->head_a));
		/////

		stacks->head_b = NULL;
		stacks->size_a = arg_count;
		stacks->size_b = 0;
		ft_memset(stacks->operations_a, '\0', 50000);
		ft_memset(stacks->operations_b, '\0', 50000);
		return (stacks);
	}


	int get_nth_highest_number(t_list *head, int n)
	{
		t_list *temp;
		int max;
		int cur_max;

		cur_max = -2147483647;
		max = -2147483647;
		temp = head;
		while(temp != NULL)
		{
			if (*((int *)temp->content) > max)
				max = *((int *)temp->content);
			temp = temp->next;
		}

		while(--n)
		{
			temp = head;
			cur_max = -2147483647;
			while(temp != NULL)
			{
				if (*((int *)temp->content) > cur_max
				&& *((int *)temp->content) < max)
					cur_max = *((int *)temp->content);
				temp = temp->next;
			}
			max = cur_max;
		}
		return(max);
	}
	t_list comp_n_copy_lst(t_list *src, void *content)
	{
		t_list *dest
		while(src)
		{
			if (content > src->content)
				ft_lst_add(dst, ft_lst_new(source->content), 4);

			src = src->next;
		}
		ft_lst_reverse(dst);
		return(dst)
	}

	void get_order(t_list *head, t_list *array_a, t_list *temp, t_list **dst)
	{
		if(!array_a)
			if (ft_lst_len(temp) > ft_lst_len(*dst))
			{
				listdel(*dst);
				dst = *temp;
			}
			else
				ft_lst_del(temp);

		if (temp->content < array_a->content)
		{
			ft_lst_add(temp, ft_lst_new(array_a->content, 4));
			get_order(array_a->next, temp, dst);
		}
		else
		{
			get_order(array_a, comp_n_cpy_lst(head, temp->content), dst);
		}
	}
	

 3 4 12 14 7 8 11 20 40 2 99 1

 3 4 7 8 11 20 40 99 sorted

 12 14 ascending

 2 1 desc

 14 13 12 11 10|6 5| 4 3 2 1 
   
int main(int arg_count, char **arg_values)
{
	t_stack *stacks;
	t_list *optimal_asc;
	t_list *optimal_desc;

	arg_values += 1;
	arg_count -= 1;
	if (arg_count == 0)
		ft_error();
	stacks = make_struct(arg_count, arg_values);

	optimal_asc = get_picking_order_asc;
	optimal_desc = get_picking_order_desc;








	return (0);
}
