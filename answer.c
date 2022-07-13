/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   answer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akoykka <akoykka@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/03 16:34:42 by akoykka           #+#    #+#             */
/*   Updated: 2022/07/14 00:23:14 by akoykka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int is_fit(t_list *list, int value)
{
	if (get_tail_value(list) < value
	&& *(int *)(list->content) > value)
		return (1);
	return (0);
}

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

	new_unsolved = NULL;
	fresh = NULL;
	len = ft_lst_count(sort->unsolved);
	if (!len)
		return ;
	if (type == DESCENDING)
	{
		fresh = solve_numbers(list_to_ints(sort->unsolved), len, DESCENDING);
		ft_lst_reverse(&fresh);
		sort->desc = fresh;
	}
	if (type == ASCENDING)
	{
		fresh = solve_numbers(list_to_ints(sort->unsolved), len, ASCENDING);
		sort->asc = fresh;
		printf("fill list after asc fill from no numbers\n");
		print_list(sort->asc);
	}

	new_unsolved = ft_lst_dup_except(sort->unsolved, fresh);
	ft_lst_del(&sort->unsolved, ft_del);
	
	sort->unsolved = new_unsolved;
}

int get_tail_value(t_list *list)
{
	if (!list)
		return (0);
	while (list->next)
		list = list->next;
	return (*(int *)list->content);
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

void delete_head_asc(t_sort *sort)
{
	t_list *target;

	if(!sort->asc)
		return;
	target = sort->asc;

	sort->asc = sort->asc->next;

	//free(target->content);
	//free(target);
}

void delete_head_desc(t_sort *sort)
{
	t_list *target;

	target = sort->desc;

	if(!target)
		return;
	sort->desc = sort->desc->next;

	//free(target->content);
	free(target);

}



void rotate_list(t_sort *sort, int stack)
{
	t_list *target;

	if (stack == ASCENDING && sort->asc && sort->asc->next)
	{
		target = sort->asc;
		sort->asc = sort->asc->next;
		(ft_lst_get_tail(sort->asc))->next = target;
		target->next = NULL;
	}
	if (stack == DESCENDING && sort->desc && sort->desc->next)
	{
		target = sort->desc;
		sort->desc = sort->desc->next;
		(ft_lst_get_tail(sort->desc))->next = target;
		target->next = NULL;
	}

	if (stack == STACK_A && sort->stack_a && sort->stack_a->next)
	{
		target = sort->stack_a;
		sort->stack_a = sort->stack_a->next;
		(ft_lst_get_tail(sort->stack_a))->next = target;
		target->next = NULL;
	}
	if (stack == STACK_B && sort->stack_b && sort->stack_b->next)
	{
		target = sort->stack_b;
		sort->stack_b = sort->stack_b->next;
		(ft_lst_get_tail(sort->stack_b))->next = target;
		target->next = NULL;
	}
	if (stack == SOLVED && sort->solved && sort->solved->next)
	{
		target = sort->solved;
		sort->solved = sort->solved->next;
		(ft_lst_get_tail(sort->solved))->next = target;
		target->next = NULL;
	}
	if (stack == UNSOLVED && sort->unsolved && sort->unsolved->next)
	{
		target = sort->unsolved;
		sort->unsolved = sort->unsolved->next;
		(ft_lst_get_tail(sort->unsolved))->next = target;
		target->next = NULL;
	}
}

void rrotate_list(t_sort *sort, int stack)
{
	t_list *target;
	t_list *temp;

	if (stack == ASCENDING && sort->asc && sort->asc->next)
	{
		target = ft_lst_get_tail(sort->asc);
		temp = sort->asc;
		while(temp->next != target)
			temp = temp->next;
		temp->next = NULL;
		target->next = sort->asc;
		sort->asc = temp;
	}
	if (stack == DESCENDING && sort->desc && sort->desc->next)
	{
		target = ft_lst_get_tail(sort->desc);
		temp = sort->desc;
		while(temp->next != target)
			temp = temp->next;
		temp->next = NULL;
		target->next = sort->desc;
		sort->desc = temp;
	}

	if (stack == STACK_A && sort->stack_a && sort->stack_a->next)
	{
		target = ft_lst_get_tail(sort->stack_a);
		temp = sort->stack_a;
		while(temp->next != target)
			temp = temp->next;
		temp->next = NULL;
		target->next = sort->stack_a;
		sort->stack_a = temp;
	}
	if (stack == STACK_B && sort->stack_b && sort->stack_b->next)
	{
		target = ft_lst_get_tail(sort->stack_b);
		temp = sort->stack_b;
		while(temp->next != target)
			temp = temp->next;
		temp->next = NULL;
		target->next = sort->stack_b;
		sort->stack_b = temp;
	}
	if (stack == SOLVED && sort->solved && sort->solved->next)
	{
		target = ft_lst_get_tail(sort->solved);
		temp = sort->solved;
		while(temp->next != target)
			temp = temp->next;
		temp->next = NULL;
		target->next = sort->solved;
		sort->solved = temp;
	}
	if (stack == UNSOLVED && sort->unsolved && sort->unsolved->next)
	{
		target = ft_lst_get_tail(sort->unsolved);
		temp = sort->unsolved;
		while(temp->next != target)
			temp = temp->next;
		temp->next = NULL;
		target->next = sort->unsolved;
		sort->unsolved = temp;
	}
}



void push_top_of_a(t_sort *sort)
{

	t_list *temp;

	if (!sort->stack_a)
		return;

	temp = sort->stack_a;
	
	sort->stack_a = sort->stack_a->next;
	
	temp->next = sort->stack_b;
	
	sort->stack_b = temp;
}

void push_top_of_b(t_sort *sort)
{
	t_list *temp;

	if (!sort->stack_b)
		return;

	temp = sort->stack_b;
	
	sort->stack_b = sort->stack_b->next;
	
	temp->next = sort->stack_a;
	
	sort->stack_a = temp;
}


void test_push_b(t_sort *sort)
{
	fill_list(sort, DESCENDING);
	printf("this is sort-desc after fill\n");
	print_list(sort->desc);

	fill_list(sort, ASCENDING);
	printf("this is sort-asc after fill\n");
	print_list(sort->asc);

	while (sort->desc)
	{
		if (sort->desc
		&& *(int *)sort->stack_a->content == *(int *)sort->desc->content)
		{
			printf("STACK_A VALUE IS IN DESC LIST\n");
			printf("stack_a is:\n");
			print_list(sort->stack_a);
			push_top_of_a(sort);
			printf("stack_a after push top is:");
			print_list(sort->stack_a);
			printf("puushed, (desc)\n");
			print_list(sort->desc);
			ft_strcat(sort->moves, "pa\n");
			delete_head_desc(sort);
			printf("deleted\n");
		}
		rotate_list(sort, STACK_A);
		print_list(sort->stack_b);
	}
	printf("rotation completed on the desc list\n");
	while (sort->asc)
	{
		if (sort->asc
		&& *(int *)sort->stack_a->content == *(int *)sort->asc->content)
		{
			printf("STACK_A VALUE IS IN ASC LIST\n");
			push_top_of_a(sort);
			printf("puushed(asc)");
			ft_strcat(sort->moves, "pa\n");
			rotate_list(sort, STACK_B);
			ft_strcat(sort->moves, "rb\n");
			delete_head_asc(sort);
			printf("stacka\n");
			print_list(sort->stack_a);
			printf("stackb\n");
			print_list(sort->stack_b);
			printf("asc\n");
			print_list(sort->asc);
		}
		rotate_list(sort, STACK_A);
		print_list(sort->stack_b);
	}
	/*
	while(sort->stack_b)
	{
		if ((sort->stack_b
			&& is_fit(sort->solved, *(int *)sort->stack_b->content))
			||(sort->stack_b 
			&& is_biggest_val(*(int *)sort->stack_b->content, sort->solved) 
			&& is_biggest_val(get_tail_value(sort->solved), sort->solved)))
		{
			printf("STACK B HEAD VALUE FITS INTO STACK A\n");
			push_top_of_b(sort);
			ft_strcat(sort->moves, "pb\n");
				// copy to solved
			ft_lst_add(&sort->solved, ft_lst_new(sort->stack_a->content, sizeof(int)));
		}

		if (sort->stack_b
			&& is_fit(sort->solved, get_tail_value(sort->stack_b)
			||(sort->stack_b
			&& is_biggest_val(get_tail_value(sort->stack_b), sort->solved) 
			&& is_biggest_val(get_tail_value(sort->solved), sort->solved))))
		{
			printf("STACK B TAIL VALUE FITS INTO STACK A\n");
			rrotate_list(sort, STACK_B);
			ft_strcat(sort->moves, "rrb\n");
			ft_lst_push_top(&(sort->stack_b), &(sort->stack_a));
			ft_strcat(sort->moves, "pb\n");
			// copy to solved
			ft_lst_add(&sort->solved, ft_lst_new(sort->stack_a->content, sizeof(int)));
		}
		
		printf("STACK_B = \n");
		print_list(sort->stack_b);
		printf("SOLVED = \n");
		print_list(sort->stack_b);
		
	




*/
	
	printf("stack_a is:\n");
	print_list(sort->stack_a);
	printf("stack_b is:\n");
	print_list(sort->stack_b);
	printf("SOLVED\n");
	print_list(sort->solved);
	printf("UNSOLVED\n");
	print_list(sort->unsolved);

}









/*
void ft_answers(t_sort *sort)
{
	printf("this is solved list\n");
	print_list(sort->solved);
	while (sort->asc || sort->desc || sort->unsolved)
	{
		if (!sort->asc && !sort->desc && !sort->stack_b)
		{
			fill_list(sort, ASCENDING);
			printf("this is sort-asc after fill\n");
			print_list(sort->asc);
			fill_list(sort, DESCENDING);
			printf("this is sort-desc after fill\n");
			print_list(sort->desc);
		}
	
		

		// CHECK IF PUSH TO B FROM A 

		if (sort->desc
			&& *(int *)sort->stack_a->content == *(int *)sort->desc->content)
		{
			printf("STACK_A VALUE IS IN DESC LIST\n");
			ft_lst_push_top(&sort->stack_a, &sort->stack_b);
			ft_strcat(sort->moves, "pa\n");
			delete_head(&sort->desc);
		}
		if (sort->asc
			&& *(int *)sort->stack_a->content == *(int *)sort->asc->content)
		{
			printf("STACK_A VALUE IS IN ASC LIST\n");
			push_top_of_a(sort); /// THIS BROKEN
			printf("puushed");
			ft_strcat(sort->moves, "pa\n");
			rotate(sort->stack_b);
			ft_strcat(sort->moves, "rb\n");
			delete_head(&sort->asc);
			printf("stacka\n");
			print_list(sort->stack_a);
			printf("stackb\n");
			print_list(sort->stack_b);
			printf("asc\n");
			print_list(sort->asc);

		}
		
		
		// CHECK HEAD STACK_B
		if ((sort->stack_b
			&& is_fit(sort->solved, *(int *)sort->stack_b->content))
			||(sort->stack_b 
				&& is_biggest_val(*(int *)sort->stack_b->content, sort->solved) && is_biggest_val(get_tail_value(sort->solved), sort->solved)))
		{
			printf("STACK B HEAD VALUE FITS INTO STACK A\n");
			ft_lst_push_top(&(sort->stack_b), &(sort->stack_a));
			ft_strcat(sort->moves, "pb\n");
				// copy to solved
			ft_lst_add(&sort->solved, ft_lst_new(sort->stack_a->content, sizeof(int)));
		}
	}

		// CHECK TAIL STACK_B
		if (sort->stack_b
			&& is_fit(sort->solved, get_tail_value(sort->stack_b)
			||(sort->stack_b
			&& is_biggest_val(get_tail_value(sort->stack_b), sort->solved) && is_biggest_val(get_tail_value(sort->solved), sort->solved))))
		{
			printf("STACK B TAIL VALUE FITS INTO STACK A\n");
			rrotate(sort->stack_b);
			ft_strcat(sort->moves, "rrb\n");
			ft_lst_push_top(&(sort->stack_b), &(sort->stack_a));
			ft_strcat(sort->moves, "pb\n");
			// copy to solved
			ft_lst_add(&sort->solved, ft_lst_new(sort->stack_a->content, sizeof(int)));
		}
		
		if (*(int *)sort->solved->content == *(int *)sort->stack_a->content)
		{
			printf("FOUND VALUE THAT IS SORTED ROTATE_A\n ");
			print_list(sort->stack_a);
			printf("THIS IS CURRENT SOLVED\n ");
			print_list(sort->solved);
			rotate(sort->solved);
			rotate(sort->stack_a);
			strcat(sort->moves, "ra\n");
		}
		else
		{
			printf("NOTHING ELSE HAPPENED SO JUST ROTATE\n");
			rotate(sort->stack_a);
			strcat(sort->moves, "ra\n");
		}
}


*/
