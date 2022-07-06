/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   answer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akoykka <akoykka@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/03 16:34:42 by akoykka           #+#    #+#             */
/*   Updated: 2022/07/06 21:46:59 by akoykka          ###   ########.fr       */
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

void fill_list(t_sort *sort, int type)
{
	t_list *fresh;
	t_list *new_unsolved;
	size_t len;

	if (!sort->unsolved)
		return;
		
	len = ft_lst_count(sort->unsolved);
	if (type == DESCENDING)
	{
		fresh = solve_numbers(list_to_ints(sort->unsolved), len, DESCENDING);
		ft_lst_reverse(&desc);
		sort->desc = fresh;
		sort->last_desc = get_tail_value(sort->desc);
	}

	if (type == ASCENDING)
	{
		fresh = solve_numbers(list_to_ints(sort->unsolved), len, ASCENDING);
		sort->asc = fresh;
		sort->last_asc = get_tail_value(sort->asc);
	}

	new_unsolved = ft_lst_dup_except(sort->unsolved, t_list *fresh);
	ft_lst_del(&sort->unsolved, ft_del);
	sort->unsolved = new_unsolved;

	/*
	printf("solved_list_len = %zu asc_list_len = %zu desc_list_len = %zu\n" ,ft_lst_count(sort->solved),ft_lst_count(asc), ft_lst_count(desc));
	printf("SOLVED LIST ::::::\n");
	print_list(sort->solved);
	printf("ASCENDING LIST ::::::\n");
	print_list(asc);
	printf("DESCENDING LIST :::::::\n");

	print_list(desc);
	sort->asc = asc;
	sort->desc = desc;

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
	*/
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

void rotate(t_list *list)
{
	ft_lst_move_one_to_tail(&list, list);
}

void rrotate(t_list *list)
{
	ft_lst_move_to_top(&list, ft_lst_get_tail(list));
}


void ft_answers(t_sort *sort);
{
	while (!asc || !desc || !unsolved)
	{
		if (*(int *)sort->head_a->contents == sort->last_asc)
			fill_list(sort, ASCENDING);
		if (*(int *)sort->head_a->contents == sort->last_desc)
			fill_list(sort, DESCENDING);
		/// Is already solved ?
		while (*(int *)sort->solved->content == *(int *)sort->stack_a->content)
		{
			rotate(sort->solved);
			rotate(sort->stack_a);
			strcat(sort->moves, "ra\n");
		}

		// Check if push to B from A
		if (sort->asc && *(int *)sort->stack_a->content == *(int *)sort->asc->content
			|| sort->desc->content && *(int *)sort->stack_a->content == *(int *)sort->desc->content)
		{
			ft_strcat(sort->moves, "pa\n");

			if (*(int *)sort->stack_a == *(int *)sort->desc)
			{
				ft_lst_push_top(sort->array_a, sort->array_b);
				delete_head(&sort->desc);
			}
			else //ASCENDING list
			{
				ft_lst_push_top(sort->array_a, sort->array_b);
				rotate(sort->stack_b);
				ft_strcat(sort->moves, "rb\n");
				delete_head(sort->asc);
			}
		}
		/// Check if push back to A in right place
		int stackbtail;
		int stackb;
		int solved_tail;
		int solved;

		stackbtail = get_tail_value(sort->stack_b);
		stackb	= *(int *)sort->stack_b->content;
		solved_tail = get_tail_value(sort->solved);
		solved = *(int)sort->solved->content;

		if (solved_tail < stackb && solved > stackb
			|| solved_tail < stackbtail && solved > stackbtail
			|| is_biggest_val(stackb, sort->solved) && is_biggest_val(solved_tail, sort->solved)
			|| is_biggest_val(stackbtail, sort->solved) && is_biggest_val(solved_tail, sort->solved))
		{
			if both are valid to switch put back the smaller 

			if(tail is smaller)
			{
				rrotate(sort->stack_b);
				ft_strcat(sort->moves, "rrb\n");
				ft_lst_push_top(&sort->stack_b, &sort->stack_a);
				ft_strcat(sort->moves, "pb\n");
			}
			if(head is smaller)
			{
				ft_lst_push_top(&sort->stack_b, &sort->stack_a);
				ft_strcat(sort->moves, "pb\n");
			}
			// copy to solved
			ft_lst_add(&sort->solved, ft_lst_new(sort->stack_a->content, sizeof(int)));
		}

		else
		{
			rotate(sort->stack_a);
			strcat(sort->moves, "ra\n");
		}
	}
}

void ft_answerss(t_sort *sort)
{
	while (!sorted)
	{
		go forward until all descending numbers have been sorted;
		and all ascending numbers are collected;
		change direction
		calculate more descending numbers (ascending coz going backwards);
		collect all descending numbers and drop all descending numbers;
		calculate more numbers and 





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
