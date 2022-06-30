/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akoykka <akoykka@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 13:23:00 by akoykka           #+#    #+#             */
/*   Updated: 2022/06/30 14:58:16 by akoykka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void print_list(t_list *list)
{
	while(list)
	{
		ft_putnbr(*(int *)list->content);
		printf("\n");
		list = list->next;
	}
}

t_list *int_arr_to_list(int *array, size_t size)
{
	size_t	i;
	t_list	*fresh;

	fresh = NULL;
	i = 0;
	while (i < size)
	{
		if (fresh == NULL)
			fresh = ft_lst_new(&array[i], sizeof(int));
		else 
			ft_lst_add(&fresh, ft_lst_new(&array[i], sizeof(int)));
		++i;
	}
	ft_lst_reverse(&fresh);

	return (fresh);
}

void ft_del(void *target, size_t size)
{
	if(!target)
		return;
	ft_memset(target, 0, size);
	free(target);
	target = NULL;
}


t_list *remove_extra_from_head(t_list **head, t_list *extra)
{
	t_list *temp;
	t_list *head_temp;

	head_temp = *head;

	while(head_temp)
	{
		temp = extra;
		while(temp)
		{
			if (*((int *)head_temp->content) == *((int *)temp->content))
				ft_lst_del_one(head, head_temp, ft_del);
			temp = temp->next;
		}
		head_temp = head_temp->next;
	}
	return(*head);
}


int *ft_invert_int_array(int *array, size_t size)
{
	size_t	high;
	size_t	low;
	int		temp;

	if (!array || !size)
		return 0;
	high = size - 1;
	low = 0;
	while(high > low)
	{
		temp = array[high];
		array[high] = array[low];
		array[low] = temp;
		--high;
		++low;
	}
	return (array);
}

void ft_print_int_array(int *array, size_t size)
{
	size_t i;

	i = 0;
	while (size > i)
	{
		printf("%i\n", *array);
		++array;
		++i;
	}
}

int *make_int_array(int arg_count, char **arg_values)
{
	size_t	i;
	int *array;

	i = 0;
	array = (int *)ft_memalloc(sizeof(int) * arg_count);
	while (arg_count > i)
	{
		array[i] = ft_atoi(arg_values[i]);
		++i;
	}
	return(array);
}

t_sort *make_sort_struct(int *array, size_t size)
{
		t_sort *new;

		new = NULL;
		new = (t_sort *)malloc(sizeof(t_sort));
		new->stack_a = int_arr_to_list(array, size);
		new->solved = solve_numbers(array, size);
		printf("\n\nThis is solved:\n");
		print_list(new->solved);
		//new->unsolved = remove_extra_from_head(int_arr_to_list(array,size), new->solved);
		new->under_sort = NULL;
		ft_memset(new->moves, '\0', 50000);
		new->stack_b = NULL;
		new->direction = 0;
		return (new);
}

int main (int arg_count, char **arg_values)
{
	int		*array;
	t_list	*fresh;
	t_sort	*sort;

	arg_values += 1;
	arg_count -= 1;

	array = make_int_array(arg_count, arg_values);
	sort = make_sort_struct(array, arg_count);
	
	//print_list(sort->unsolved);

	return (0);
}

/*answer = solve_numbers_asc(array, arg_count);
	while (unsolved)
	{
		if (!under_sort)
		{
			fill_under_sort()
			get_direction()
		}
		while(*(under_sort->contents) == *(stack_a->contents)
			push a_to_b;

		while (stack_b->contents < solved->contents &&
			stack_b->contents > get_tail_value(solved))
			push b_to_a;

		rotate(sort_struct, sort->direction);
	}



char **parse_input(int arg_count, char **arg_values)
{
	/// miten tietaa onko inputissa useampi luku

	/// miten tarkistaa onko kaikki lukuja ja valilla int_min int_max

	/// lopulta muokkaus muotoon char **array

	size_t i;
	size_t new_i;
	char **new;

	i = 0;
	new_i = 0;
	new = (char **)ft_memalloc(sizeof(char *) * arg_count + 1);

	while (arg_count > i && *(arg_values[i]))
		is_number()
		is_in_int_range()
		new[new_i] = copynumber
}
*/
