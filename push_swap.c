/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akoykka <akoykka@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 10:09:42 by akoykka           #+#    #+#             */
/*   Updated: 2022/06/08 16:12:35 by akoykka          ###   ########.fr       */
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

t_list *make_list(int *array, int size)
{
	t_list *head = NULL;
	t_list *new;

	
	while(size--)
	{
		new = ft_lst_new(&array[size], 4);
		ft_lst_add(&head, new);
	}
	return (head);
}





t_stack *make_struct(int arg_count, char **argv)
{
	t_stack *stacks;
	t_list *head_array_a;
	int *array;

	if	(arg_count == 1)
		*argv =	ft_strsplit(*argv);
	
	stacks = (t_stack *)ft_memalloc(sizeof(t_stack));
	array = char_array_to_int_array(arg_count, argv);

	ft_print_array(array, arg_count);
	stacks->head_a = make_list(array, arg_count);
	ft_printf("Print list: head_a\n");
	print_list(stacks->head_a);
	stacks->head_b = NULL;
	printf("Length of list is: %zu\n", ft_lst_count(stacks->head_a));
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

int is_sorted(t_list *head, int sort)
{
	int curr_element_value;
	int next_element_value;
	static int i = 0;

	while (head->next)
	{
		curr_element_value = *((int *)head->content);
		next_element_value = *((int *)(head->next)->content);
		if (curr_element_value > next_element_value
			&& sort == ASCENDING)
			{
			printf("not sorted %d\n", i++);
			return (0);
			}
		if (curr_element_value < next_element_value
			&& sort == DESCENDING)
			{
			printf("not sorted %d\n", i++);
			return (0);
			}
		head = head->next;
	}
	return (1);
}

void bubble_sort_a(t_stack *stacks, t_list *head)
{
	int	curr_element_value; ///valiaikainen
	int	next_element_value;
	int low;
	int high;

	
	high = get_nth_highest_number(head, 1);
	low  = get_nth_highest_number(head, stacks->size_a);
	
	while (!is_sorted(stacks->head_a, ASCENDING))
	{
		curr_element_value = *((int *)(stacks->head_a)->content);
		next_element_value = *((int *)(((stacks->head_a)->next)->content));
		
		
		ft_printf("high is %i, Low is %i \n", high, low);
		ft_printf("Curr %i  next %i\n", curr_element_value, next_element_value);
		
		if (curr_element_value < next_element_value
			|| (curr_element_value == high && next_element_value == low))
		{
			rotate(stacks, 'a');
			write(1, "equrotate\n", 10);
			ft_strcat(stacks->operations_a, "r");
		}
		else
		{
			swap(stacks, 'a');
			write(1, "swap\n", 5);
			ft_strcat(stacks->operations_a, "s");
		}
	}
}

void bubble_sort_b(t_stack *stacks, t_list *head)
{
	int	curr_element_value; ///valiaikainen
	int	next_element_value;
	int low;
	int high;

	
	high = get_nth_highest_number(head, 1);
	low  = get_nth_highest_number(head, stacks->size_b);
	
	while (!is_sorted(stacks->head_b, DESCENDING))
	{
		curr_element_value = *((int *)(stacks->head_b)->content);
		next_element_value = *((int *)(((stacks->head_b)->next)->content));
		
		
		ft_printf("high is %i, Low is %i \n", high, low);
		ft_printf("Curr %i  next %i\n", curr_element_value, next_element_value);
		
		if (curr_element_value > next_element_value
			|| (curr_element_value == low && next_element_value == high))
		{
			rotate(stacks, 'b');
			write(1, "equrotate\n", 10);
			ft_strcat(stacks->operations_b, "r");
		}
		else
		{
			swap(stacks, 'b');
			write(1, "swap\n", 5);
			ft_strcat(stacks->operations_b, "s");
		}
	}
}



void split_list(t_stack *stacks)
{
	int pivot;
	int loop;
	int contents; 
	t_list *temp;


	pivot = get_nth_highest_number(stacks->head_a, stacks->size_a / 2);
	printf("pivot value is:%i\n", pivot);
	int tempnumber = stacks->size_a / 2; /// en jaksanu keksia keksi sina tulevaisuuden-atte
	loop = stacks->size_a;
	while(loop--) //&& stacks->size_b == tempnumber)
	{
		contents = *((int *)(stacks->head_a)->content);
		if (contents < pivot)
			push_to(stacks, 'b');
		else
			rotate(stacks, 'a');
	}
	printf("b_stack size after split is %i\n", stacks->size_b);
}



int main(int arg_count, char **arg_values)
{
	t_stack *stacks;
	
	arg_values += 1;
	arg_count -= 1;
	if (arg_count == 0)
		ft_error();
	stacks = make_struct(arg_count, arg_values);
	split_list(stacks);
	printf("list A post split:\n");
	print_list(stacks->head_a);
	printf("list B post split:\n");
	print_list(stacks->head_b);
	// swap(stacks, 'a');
	// printf("Swap a:\n");
	// print_list(stacks->head_a);
	//rotate(stacks, 'a');
	//printf("Rotate a:\n");
	// print_list(stacks->head_a);
	// rotate(stacks, 'a');
	// printf("Rotate a:\n");
	print_list(stacks->head_a);
	
	bubble_sort_a(stacks, stacks->head_a);
	bubble_sort_b(stacks, stacks->head_b);
	print_list(stacks->head_a);
	ft_printf("Operations a are :%s\n strlen is %i\n",stacks->operations_a, ft_strlen(stacks->operations_a));
	print_list(stacks->head_b);
	ft_printf("Operations b are :%s\n strlen is %i\n",stacks->operations_b, ft_strlen(stacks->operations_b));
	return (0);
}
