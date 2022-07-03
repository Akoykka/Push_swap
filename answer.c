/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   answer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akoykka <akoykka@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/03 16:34:42 by akoykka           #+#    #+#             */
/*   Updated: 2022/07/03 19:16:01 by akoykka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int *list_to_ints(t_list *list)
{
	int *array;
	int i;

	i = 0;
	array = ft_memalloc(sizeof(int) * ft_lst_count(list));
	while(list)
	{
		array[i] = *(int *)(list->content);
		++i;
		list = list->next;
	}
	return (array);
}

void fill_under_sort(t_sort *sort)
{
	t_list *asc;
	t_list *desc;
	size_t len;

	len = ft_lst_count(sort->unsolved);
	asc = solve_numbers(list_to_ints(sort->unsolved), len, ASCENDING);
	desc = solve_numbers(list_to_ints(sort->unsolved), len, DESCENDING);
	if (ft_lst_count(asc) > ft_lst_count(desc))
	{
		sort->direction = BACKWARD;
		sort->under_sort = asc;
		ft_lst_del(&desc, ft_del);
		return ;
	}
	sort->direction = FORWARD;
	sort->under_sort = desc;
	ft_lst_del(&asc, ft_del);
}

int check_stack_a_value(t_sort *sort)
{
	(*(int *)((sort->under_sort)->content) 
			== *(int *)((sort->stack_a)->content))
	push_to_b()

}

int check_stack_b_value(t_sort *sort)
{



	
}


void push_from_b_to_a(t_sort *sort)
{



}

void ft_answer(t_sort *sort)
{
	while (sort->unsolved)
	{
		if (!sort->under_sort)
			fill_under_sort(sort);
		//while (*(int *)((sort->under_sort)->content) 
		//	== *(int *)((sort->stack_a)->content))
			//push_from_a_to_b_stack(sort);
		while (check_stack_a_value(sort))
			push_to_b()

		while (check_stack_b_value(sort))
			push_to_a;
		//while ( *(int *)((sort->stack_b)->content)
		//	< *(int *)((sort->solved)->content) 
		//	&& *(int *)(sort->stack_a)->contents > get_tail_value(sort->solved))
		//	push_from_b_to_a_stack(sort);

		rotate(sort, sort->direction);
	}
}
