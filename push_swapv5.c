/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swapv5.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akoykka <akoykka@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 12:07:05 by akoykka           #+#    #+#             */
/*   Updated: 2022/07/05 10:54:56 by akoykka          ###   ########.fr       */
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

void get_longest_branch(t_mnode *tree, t_solve *answer, size_t depth)
{
	size_t i;

	i = 0;
	//if (!tree)
	//{
	//	printf("endofbranch\n");
	//	return;
	//}

	(answer->current)[depth] = *(int *)(tree->content);
	//////
	//printf("copy_to_current depth: %zu\n", depth);
	//ft_print_int_array(answer->current, depth);

	if (depth > answer->answer_depth) ////depth to -1 or something first possible
	{
		answer->answer_depth = depth;
		ft_memcpy(answer->answer, answer->current, sizeof(int) * (depth + 1));
		////////
		//printf("longest found:\n");
		//ft_print_int_array(answer->answer, answer->answer_depth + 1);
	}

	while (tree->next_size > i)
	{
		//printf("going down(longest_branch):\n");
		/////
		get_longest_branch((tree->next)[i], answer, depth + 1);
		++i;
	}
}

int move_array_pointer_and_adjust_size(int *array, size_t size)
{
	size_t i;

	i = 0;

	while (i < size && array[i] >= array[0])
	{
		++i;
	}
	//printf("move pointer %zu forward\n", i);
	return (i);
}
void get_insert_point(t_mnode *mtree, t_insert *temp, size_t depth)
{
	size_t i;

	i = 0;
	if (!mtree)
	{
		//printf("end of mtree (depth:%zu\n", depth);
		return ;
	}
	if (temp->value < *(int *)(mtree->content))
	{
		//printf("temp value smaller (temp: %i mtree->content %i\n", temp->value, *(int *)mtree->content);
		return ;
	}
	if (temp->max_depth < depth || temp->max_depth == 0)
	{

		temp->max_depth = depth;
		temp->insert_point = mtree;
		//printf("insert_point found: max_depth %zu\n", temp->max_depth);
		//printf("insert point addr: %p\n", temp->insert_point);
	}
	while (mtree->next_size > i)
	{

		get_insert_point((mtree->next)[i], temp, depth + 1);
		++i;
	}
}

void add_to_tree(t_mnode *mtree, void *content, size_t content_size)
{
	t_insert *temp;

	temp = (t_insert *)ft_memalloc(sizeof(t_insert));
	temp->value = *(int *)content;
	temp->max_depth = 0;
	temp->insert_point = NULL;
	get_insert_point(mtree, temp, 0);
	ft_mnode_insert(temp->insert_point, ft_mnode_new(content, content_size));
	free(temp);
}

t_solve *solve_numbers_asc(int *array, size_t size)
{
	size_t i;
	size_t forward = 0;
	t_mnode *mtree;
	t_solve	*answer;

	answer = (t_solve *)ft_memalloc(sizeof(t_solve));
	mtree = NULL;
	while (size)
	{
		i = 0;
		while (size > i)
		{
			if (array[i] >= array[0])
			{
				if	(mtree == NULL)
				{
					mtree = ft_mnode_new(&array[i], sizeof(int));
				}
				else
				{
					add_to_tree(mtree, &array[i], sizeof(int));
				}
			}
			++i;
		}
		get_longest_branch(mtree, answer, 0);
		forward = move_array_pointer_and_adjust_size(array, size);
		array += forward;
		size -= forward;
	}
	return (answer);
}

t_sort *make_sort_struct(int *array, size_t size)
{
		t_sort *new;

		new = NULL;
		new = (t_sort *)malloc(sizeof(t_sort));
		new->stack_a = int_arr_to_list(array, size);
		new->solved = int_arr_to_list(solve_numbers_asc(array, size), size);
		new->unsolved = remove_extra_from_head(int_arr_to_list(array,size), new->solved);
		new->under_sort = NULL
		ft_memset(new->moves, '\0', 50000);
		new->stack_b = NULL;
		new->direction = 0;
}

int main (int arg_count, char **arg_values)
{
	int		*array;
	t_solve *answer;
	t_list	*fresh;
	t_sort	*sort;

	arg_values += 1;
	arg_count -= 1;

	//arg_values = parse_input(arg_count, arg_values);
	array = make_int_array(arg_count, arg_values);
	//ft_print_int_array(array, (size_t)arg_count);
	answer = solve_numbers_asc(array, arg_count);
	printf("ASCENDING:\n the answer_depth is %zu\n", answer->answer_depth + 1);
	ft_print_int_array(answer->answer, (answer->answer_depth + 1));


	//printf("\n\n this is normal\n\n");
	//ft_print_int_array(array, (size_t)arg_count);
	//printf("\n\n this is invert\n\n");

	array = ft_invert_int_array(array, (size_t)arg_count);
	//ft_print_int_array(array, (size_t)arg_count);
	answer = solve_numbers_asc(array, arg_count);
	printf("DESCENDING:\n the answer_depth is %zu\n", answer->answer_depth + 1);
	ft_print_int_array(answer->answer, (answer->answer_depth + 1));
	//make_sort_struct(array);
	printf("testing my arr to list and printlist: \n");
	fresh = int_arr_to_list(array, arg_count);
	print_list(fresh);

	sort = make_sort_struct(array, arg_count);
	print_list(sort->solved);
	print_list(sort->stack_a);
	print_list(sort->unsolved);

	return (0);
}

/*
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


/*
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
/*
	while (unsolved)
	{
		if stack_a value is in lists


		while stack_b first or last value is smaller than next solved
			push first values first if true
				record move
				push b to a
				push corresponding to solved list
				check_lists if asc or desc empty


					sorted 1 2 3 4 5 6 7 11 35 49

	              50 40 30 20 10 | 1 2 |3 4 5 6 7

				   50 40 30 20 10 |9 16| 17 19 44 80

								|1 2| 3 4 5 6 7 8 11 41 35 49


				7 1 8 2 3 9

				sorted = 1 4 7 9 11 12 20 21 28 49

				asc =  2 23 29 31 34
				desc =

				esiintymisjarjestyksessa 29 26 20 8 9 10 18 16 22 24 30

				unsorted = 27 12 23 7 28 4 25 5 21



	6 8 47 24 38 1 17 46 14 10 4 27 7 35 26 18 45 48 16 32 25 44 36 42 43 3 15 9 40 30 11 37 5 22 12 50 41 2 33 39 23 29 20 21 31 28 13 19 49 34




 				11 15 32 45
				-> and descending
				 10 4 27 7 35 26 18 48 16  25 44 36 42 43 3 9 40 3037 5 22 12


32 40			<- ascending
				10 4 27 7 35 26 18 45 48 16  25 44 36 42 43 3 15 9  30 11 37 5 22 12



				10 4 27 7 35 26 18 45 48 16 32 25 44 36 42 43 3 15 9 40 30 11 37 5 22 12



				 40 36 32 27 10

				-> and ascending
				  4 7 35 26 18 45 48 16  25 44  42 43 3 15 9 30 11 37 5 22 12
	}
*/



char array



muutetaan int arrayksi 

lasketaan structiin int arraysta luvut

