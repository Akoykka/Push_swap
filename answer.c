/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   answer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akoykka <akoykka@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/03 16:34:42 by akoykka           #+#    #+#             */
/*   Updated: 2022/07/05 14:54:39 by akoykka          ###   ########.fr       */
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
	printf("solved_list_len = %zu asc_list_len = %zu desc_list_len = %zu\n" ,ft_lst_count(sort->solved),ft_lst_count(asc), ft_lst_count(desc));
	printf("SOLVED LIST ::::::\n");
	print_list(sort->solved);
	printf("ASCENDING LIST ::::::\n");
	print_list(asc);
	printf("DESCENDING LIST :::::::\n");
	ft_lst_reverse(&desc);
	print_list(desc);

	if (ft_lst_count(asc) > ft_lst_count(desc))
	{
		printf("direction is Backwards list is ascending\n");
		sort->direction = BACKWARD;
		sort->under_sort = asc;
		ft_lst_del(&desc, ft_del);
		return ;
	}
	printf("direction is Forward list is descending\n");
	sort->direction = FORWARD;
	sort->under_sort = desc;
	ft_lst_reverse(&sort->under_sort);
	ft_lst_del(&asc, ft_del);
}

int get_tail_value(t_list *list)
{
	if (!list)
		return (0);
	while (list->next)
		list = list->next;
	return (*(int *)list->content);
}

int check_stack_a(t_sort *sort)
{
	if (*(int *)((sort->under_sort)->content) 
		== *(int *)((sort->stack_a)->content))
		return 1;
	return 0;
}

int is_biggest_val(int value, t_list *compare)
{
	while(compare)
	{
		if (value < *(int *)compare->content)
			return (0);
			compare = compare->next;
	}
	return (1);
}

int check_stack_b(t_sort *sort)
{
	if ((*(int *)(sort->stack_b->content) < *(int *)(sort->solved->content)
		&& *(int *)(sort->stack_b->content) > get_tail_value(sort->solved))
		|| ft_lst_count(sort->stack_a) == 1
		|| is_biggest_val(*(int *)sort->stack_b->content, sort->stack_a))
		return 1;
	return (0);
}

void delete_head(t_list **head)
{
	t_list *temp;

	if	(!head || !*head)
		return ;
	temp = *head;

	*head = temp->next;
	if (temp->content_size && temp->content)
	{
		free(temp->content);
		temp->content = NULL;
	}
	free(temp);
	temp = NULL;
}

void rotate(t_list *list, int direction)
{
	if (direction == FORWARD)
		ft_lst_move_one_to_tail(&list, list);
	else
		ft_lst_move_to_top(&list, ft_lst_get_tail(list));
}

void ft_answers(t_sort *sort);
{
	while (!is_solved(sort->stack_a))
	{
		
		if !asc
			fill asc;

		if !desc
			fill des;

		check if desc and asc if top of stack_a == descending or ascending 
		{
		if
			push top of stack a to b if DESCENDING
		else
			rrotate if ascending; 
			then top of stack a to b;

		destroy corresponding linked list node as it is now in stack b
		
		}
		
		check if top or tail of stack_b can be inserted in the 
		stack_a (if head and tail of stack_a are found in solved
		and tail is lower and head is higher)
		{
			then copy and add it to the solved
			push stack top of stack_b to stack_a
		}

		else
			rotate stack a 


	}

}




*/





void ft_answer(t_sort *sort)
{
	int loop;
	loop = 1;

	while (sort->unsolved)
	{
		if (!sort->under_sort && !sort->stack_b)
		{
			fill_under_sort(sort);
			printf("loop %i under sort after filling:\n", loop);
			print_list(sort->under_sort);
		}
		while (sort->stack_a && check_stack_a(sort))
		{
			delete_head(&(sort->under_sort));
			ft_lst_push_top(&sort->stack_a, &sort->stack_b);
			ft_strcat(sort->moves, "pa\n");
			printf("loop %i stack_a:\n", loop);
			print_list(sort->stack_a);
			printf("loop %i under_sort:\n", loop);
			print_list(sort->under_sort);
		}

		while (sort->stack_b && check_stack_b(sort))
		{
			ft_lst_push_top(&sort->unsolved, &sort->solved);
			rotate(sort->solved, sort->direction);
			ft_lst_push_top(&sort->stack_b, &sort->stack_a);
			ft_strcat(sort->moves, "pb\n");
		}

		if (*(int *)((sort->stack_a)->content) //stack_a = solved
			== *(int *)((sort->solved)->content))
		{
			printf("loop %i rotate solved \n", loop);
			rotate(sort->solved, sort->direction);
		}
		rotate(sort->stack_a, sort->direction);
		printf("loop %i rotated stack_a \n", loop);
		print_list(sort->stack_a);
		ft_strcat(sort->moves, "ra\n");
		//printf("loop %i current moves %s\n", loop, sort->moves);
		loop++;
	}
}
