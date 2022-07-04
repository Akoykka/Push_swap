/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   answer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akoykka <akoykka@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/03 16:34:42 by akoykka           #+#    #+#             */
/*   Updated: 2022/07/04 20:28:19 by akoykka          ###   ########.fr       */
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

int check_stack_b(t_sort *sort)
{
	if ((*(int *)((sort->stack_b)->content) < *(int *)(sort->solved->content)
		&& *(int *)((sort->stack_b)->content) > get_tail_value(sort->solved))
		|| ft_lst_count(sort->stack_a) == 1)
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
