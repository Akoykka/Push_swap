/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   answer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akoykka <akoykka@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/03 16:34:42 by akoykka           #+#    #+#             */
/*   Updated: 2022/07/26 14:17:44 by akoykka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void count_moves(char *str)
{
	int moves;

	moves = 0;
	while(*str)
	{
		if (*str == '\n')
			++moves;
		++str;
	}
	printf("move amount is approx: %i\n", moves);
}

int is_fit_stack_b_head(t_sort *sort)
{
	int value;

	value = *(int *)sort->stack_b->content;
	
	if (get_tail_value(sort->solved) < value
		&& *(int *)(sort->solved->content) > value)
		return (1);

	if (get_tail_value(sort->solved) < value
		&& is_smallest_val(*(int *)sort->solved->content, sort->solved))
		return(1);

	if (is_smallest_val(*(int *)sort->solved->content, sort->solved) 
		&& value < *(int *)sort->solved->content)
		return (1);

	return (0);
}

int is_fit_stack_b_tail(t_sort *sort)
{
	int value;
	
	value = get_tail_value(sort->stack_b);

	if (get_tail_value(sort->solved) < value
		&& *(int *)(sort->solved->content) > value)
		return (1);

	if (get_tail_value(sort->solved) < value
		&& is_smallest_val(*(int *)sort->solved->content, sort->solved))
		return(1);

	if (is_smallest_val(*(int *)sort->solved->content, sort->solved) 
		&& value < *(int *)sort->solved->content)
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
	t_list *fresh = NULL;
	t_list *new_unsolved = NULL;
	size_t len;

	len = ft_lst_count(sort->unsolved);
	if (len == 1) // TEMP FIX
	{
		if (type == DESCENDING)
		{
			sort->desc = sort->unsolved;
			sort->unsolved = NULL;
		}
		if (type == ASCENDING)
		{
			sort->asc = sort->unsolved;
			sort->unsolved = NULL;
		}
		return ;
	}
	if (len == 0)
	{
		printf("tried to fill list, unsolved is empty\n");
		return ;
	}
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
	}
	//if(len > 1)
	new_unsolved = ft_lst_dup_except(sort->unsolved, fresh);
	//ft_lst_del(&sort->unsolved, ft_del);
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


int is_smallest_val(int value, t_list *compare)
{
	while(compare)
	{
		if (value > *(int *)compare->content)
			return (0);
		compare = compare->next;
	}
	return (1);
}

void delete_head_asc(t_sort *sort)
{
	t_list *target;

	if(!sort->asc)
		return;
	target = sort->asc;

	sort->asc = sort->asc->next;

	//free(target->content);
	free(target);
	target = NULL;
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
	target = NULL;

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
		sort->asc = target;
	}
	if (stack == DESCENDING && sort->desc && sort->desc->next)
	{
		target = ft_lst_get_tail(sort->desc);
		temp = sort->desc;
		while(temp->next != target)
			temp = temp->next;
		temp->next = NULL;
		target->next = sort->desc;
		sort->desc = target;
	}

	if (stack == STACK_A && sort->stack_a && sort->stack_a->next)
	{
		target = ft_lst_get_tail(sort->stack_a);
		temp = sort->stack_a;
		while(temp->next != target)
			temp = temp->next;
		temp->next = NULL;
		target->next = sort->stack_a;
		sort->stack_a = target;
	}
	if (stack == STACK_B && sort->stack_b && sort->stack_b->next)
	{
		target = ft_lst_get_tail(sort->stack_b);

		temp = sort->stack_b;

		while(temp->next != target)
			temp = temp->next;

		temp->next = NULL;

		target->next = sort->stack_b;

		sort->stack_b = target;
	}
	if (stack == SOLVED && sort->solved && sort->solved->next)
	{
		target = ft_lst_get_tail(sort->solved);
		temp = sort->solved;
		while(temp->next != target)
			temp = temp->next;
		temp->next = NULL;
		target->next = sort->solved;
		sort->solved = target;
	}
	if (stack == UNSOLVED && sort->unsolved && sort->unsolved->next)
	{
		target = ft_lst_get_tail(sort->unsolved);
		temp = sort->unsolved;
		while(temp->next != target)
			temp = temp->next;
		temp->next = NULL;
		target->next = sort->unsolved;
		sort->unsolved = target;
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
	int i;

	i = 6;
	while (i--)
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
				printf("stack_a after push top is:\n");
				print_list(sort->stack_a);
				printf("puushed, (desc)\n");
				print_list(sort->desc);
				ft_strcat(sort->moves, "pa\n");
				delete_head_desc(sort);
				printf("deleted\n");
			}
			else
			{
				rotate_list(sort, STACK_A);
				ft_strcat(sort->moves, "ra\n");
			}
		}
		printf("rotation completed on the desc list\n");
		print_list(sort->stack_a);
		print_list(sort->stack_b);
		while (sort->asc)
		{
			if (sort->asc
			&& *(int *)sort->stack_a->content == *(int *)sort->asc->content)
			{
				printf("STACK_A VALUE IS IN ASC LIST\n");
				push_top_of_a(sort);
				printf("puushed(asc)\n");
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
			else
				rotate_list(sort, STACK_A);
		}
		
		while(sort->stack_b)
		{
			if (sort->stack_b
				&& is_fit_stack_b_head(sort))
			{
				printf("STACK B HEAD VALUE FITS INTO STACK A\n");
				push_top_of_b(sort);
				ft_strcat(sort->moves, "pb\n");
				ft_lst_add(&sort->solved, ft_lst_new(sort->stack_a->content, sizeof(int)));
			}
		
			else if (sort->stack_b
				&& is_fit_stack_b_tail(sort))
			{
				//printf("this is stack b\n");
				//print_list(sort->stack_b);
				printf("STACK B TAIL VALUE FITS INTO STACK A\n");
				//count_moves(sort->moves);
				//printf("unsolved len = %zu\n", ft_lst_count(sort->unsolved));
				//printf("solved len = %zu\n", ft_lst_count(sort->solved));
				//printf("stack_a len = %zu\n", ft_lst_count(sort->stack_a));
				//printf("stack_b len = %zu\n", ft_lst_count(sort->stack_b));
				//printf("asc len = %zu\n", ft_lst_count(sort->asc));
				//printf("desc len = %zu\n", ft_lst_count(sort->desc));
				//print_list(sort->solved);
				rrotate_list(sort, STACK_B);
				ft_strcat(sort->moves, "rrb\n");
				push_top_of_b(sort);
				printf("pushed_top_of_b\n");
				ft_strcat(sort->moves, "pb\n");
				ft_lst_add(&sort->solved, ft_lst_new(sort->stack_a->content, sizeof(int)));
			}
			else 
			{
				if( *(int *)sort->stack_a->content == *(int *)sort->solved->content)
					rotate_list(sort, SOLVED);
				rotate_list(sort, STACK_A);
				ft_strcat(sort->moves, "ra\n");
				printf("thisStackA\n");
				print_list(sort->stack_a);
				printf("up stack a down stack b\n");
				print_list(sort->stack_b);
				printf("Endofb\n");
			}
		}
		
	}
	////END !
	printf("stack_a is:\n");
	print_list(sort->stack_a);
	printf("stack_b is:\n");
	print_list(sort->stack_b);
	printf("SOLVED\n");
	print_list(sort->solved);
	printf("UNSOLVED\n");
	print_list(sort->unsolved);
	printf("%s", sort->moves);
	count_moves(sort->moves);
	printf("unsolved len = %zu\n", ft_lst_count(sort->unsolved));
	printf("solved len = %zu\n", ft_lst_count(sort->solved));
	printf("stack_a len = %zu\n", ft_lst_count(sort->stack_a));
	printf("stack_b len = %zu\n", ft_lst_count(sort->stack_b));
	printf("asc len = %zu\n", ft_lst_count(sort->asc));
	printf("desc len = %zu\n", ft_lst_count(sort->desc));
	print_list(sort->stack_a);
	
}

void push_stack_a_desc(t_sort *sort)
{
	if((sort->desc
		&& *(int *)sort->stack_a->content == *(int *)sort->desc->content))
	{
		push_top_of_a(sort);
		ft_strcat(sort->moves, "pa\n");
		delete_head_desc(sort);
	}
}

void push_stack_a_asc(t_sort *sort)
{
	if((sort->asc
		&& *(int *)sort->stack_a->content == *(int *)sort->asc->content))
	{
		push_top_of_a(sort);
		rrotate_list(sort, STACK_B);
		ft_strcat(sort->moves, "pa\n");
		ft_strcat(sort->moves, "rrb\n");
		delete_head_asc(sort);
	}
}

void push_stack_b_head(t_sort *sort)
{
	if (sort->stack_b && is_fit_stack_b_head(sort))
	{
		push_top_of_b(sort);
		ft_strcat(sort->moves, "pb\n");
		ft_lst_add(&sort->solved, ft_lst_new(sort->stack_a->content, sizeof(int)));
		sort->action_executed = 1;
	}
}

void push_stack_b_tail(t_sort *sort)
{
	if (sort->action_executed)
	{
		sort->action_executed = 0;
		return ;
	}
	if (sort->stack_b && is_fit_stack_b_tail(sort))
	{
		rrotate_list(sort, STACK_B);
		push_top_of_b(sort);
		ft_strcat(sort->moves, "rrb\npb\n");
		ft_lst_add(&sort->solved, ft_lst_new(sort->stack_a->content, sizeof(int)));
		sort->action_executed = 1;
	}
}

void rotate_stack_a(t_sort *sort)
{
	if (sort->action_executed)
	{
		sort->action_executed = 0;
		return ;
	}
	if (*(int *)sort->stack_a->content == *(int *)sort->solved->content)
		rotate_list(sort, SOLVED);
	rotate_list(sort, STACK_A);
	
}
int is_sorted(t_sort *sort)
{
	if (sort->unsolved ||sort->asc || sort->desc || sort->stack_b)
		return (0);
	return(1);
}


void answersfive(t_sort *sort)
{
	size_t stopcondition;
	
	stopcondition = ft_lst_count(sort->stack_a);
	//while (ft_lst_count(sort->solved) != stopcondition)
	while (sort->unsolved || sort->asc || sort->desc)
	{
		if(!sort->stack_b)
		{
			fill_list(sort, ASCENDING);
			fill_list(sort, DESCENDING);
		}
		push_stack_a_desc(sort);
		push_stack_a_asc(sort);
		if (sort->stack_b &&
			get_tail_value(sort->stack_b) < *(int *)sort->stack_b->content)
		{
			push_stack_b_tail(sort);
			push_stack_b_head(sort);
		}
		else
		{
			push_stack_b_head(sort);
			push_stack_b_tail(sort);
		}
		count_moves(sort->moves);
		printf("unsolved len = %zu\n", ft_lst_count(sort->unsolved));
		printf("solved len = %zu\n", ft_lst_count(sort->solved));
		printf("stack_a len = %zu\n", ft_lst_count(sort->stack_a));
		printf("stack_b len = %zu\n", ft_lst_count(sort->stack_b));
		printf("asc len = %zu\n", ft_lst_count(sort->asc));
		printf("desc len = %zu\n", ft_lst_count(sort->desc));
		printf("this is asc a : \n");
		print_list(sort->asc);
		rotate_stack_a(sort);
	}
	printf("stack_a is:\n");
	print_list(sort->stack_a);
	printf("stack_b is:\n");
	print_list(sort->stack_b);
	printf("SOLVED\n");
	print_list(sort->solved);
	printf("UNSOLVED\n");
	print_list(sort->unsolved);
	printf("%s", sort->moves);
	count_moves(sort->moves);
	printf("unsolved len = %zu\n", ft_lst_count(sort->unsolved));
	printf("solved len = %zu\n", ft_lst_count(sort->solved));
	printf("stack_a len = %zu\n", ft_lst_count(sort->stack_a));
	printf("stack_b len = %zu\n", ft_lst_count(sort->stack_b));
	printf("asc len = %zu\n", ft_lst_count(sort->asc));
	printf("desc len = %zu\n", ft_lst_count(sort->desc));
	printf("this is stack a : \n");
	print_list(sort->stack_a);
}










/*
fill list if stack b empty;

pickup stuff on the lists - asc desc problem nope not a problem
distribute what you can 

only one thing can be done 

then rotate 
also rotate solved 


scenario 1

stack b empty -> asc list pickup       normal push

scenario 2

stack b empty -> desc list pickup		normal push

scenario 3

stack b has asc number in it -> asc number pickup 

push + rrotate

scenario 4

stack b has asc number in it -> desc number pickup

5 4 3 2 1 10 20 30 40

10 4 

scenario 5

stack b has desc number in it -> asc number pickup

10

scenario 6 

stack b has desc number in it -> desc number pickup

*/