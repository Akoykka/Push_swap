/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akoykka <akoykka@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 12:07:05 by akoykka           #+#    #+#             */
/*   Updated: 2022/06/28 22:39:45 by akoykka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

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
	//printf("trying to find insert point\n");
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
				//printf("i=%zutrying to insert %i\tcurrent low is %i\n",i, array[i], array[0]);
				if	(mtree == NULL)
				{
					//printf("mtree is null. making a new\n");
					mtree = ft_mnode_new(&array[i], sizeof(int));
				}
				else
				{
					//printf("mtree exists, adding on to it\n");
					add_to_tree(mtree, &array[i], sizeof(int));
				}
			}
			++i;
		}
		//get_answer_compare_and_save()

		get_longest_branch(mtree, answer, 0);
		ft_mnode_destroy(&mtree);
		forward = move_array_pointer_and_adjust_size(array, size);
		array += forward;
		size -= forward;
	}
	return (answer);
}




int main (int arg_count, char **arg_values)
{
	int		*array;
	t_solve *answer;

	arg_values += 1;
	arg_count -= 1;

	array = make_int_array(arg_count, arg_values);
	//ft_print_int_array(array, (size_t)arg_count);
	answer = solve_numbers_asc(array, arg_count);
	printf("ASCENDING:\n the answer_depth is %zu\n", answer->answer_depth + 1);
	//ft_print_int_array(answer->answer, (answer->answer_depth + 1));


	//printf("\n\n this is normal\n\n");
	//ft_print_int_array(array, (size_t)arg_count);
	//printf("\n\n this is invert\n\n");

	array = ft_invert_int_array(array, (size_t)arg_count);
	//ft_print_int_array(array, (size_t)arg_count);
	answer = solve_numbers_asc(array, arg_count);
	printf("DESCENDING:\n the answer_depth is %zu\n", answer->answer_depth + 1);
	//ft_print_int_array(answer->answer, (answer->answer_depth + 1));


	return (0);
}
/*
	 make_sort_struct
	{
		unsolved = copy_stack(stack_a)
		move ascending numbers to solved;
		move ascending numbers to asc;
		move descending numbers to desc;
	}



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





	}
	*/