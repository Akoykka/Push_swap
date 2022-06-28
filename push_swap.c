/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akoykka <akoykka@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 12:07:05 by akoykka           #+#    #+#             */
/*   Updated: 2022/06/24 15:30:41 by akoykka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"


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
	if (!tree)
		return;

	(answer->current)[depth] = *(int *)(tree->content);

	if (depth > answer->answer_depth)
	{
		answer->answer_depth = depth;
		ft_memcpy(answer->answer, answer->current, depth);
	}

	while (tree->next_size > i)
	{
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
	printf("move pointer %zu forward\n", i);
	return (i);
}
void get_insert_point(t_mnode *mtree, t_insert *temp, size_t depth)
{
	size_t i;

	i = 0;
	if (!mtree)
		return ;
	if (temp->value < *(int *)(mtree->content))
		return ;
	if (temp->max_depth < depth)
	{
		temp->max_depth = depth;
		temp->insert_point = mtree;
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
				printf("i=%zutrying to insert %i\tcurrent low is %i\n",i, array[i], array[0]);
				if	(mtree == NULL)
					ft_mnode_new(&array[i], sizeof(int));
				else
					add_to_tree(mtree, &array[i], sizeof(int));
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

void ft_print_int_array(int *array, size_t size)
{
	while (size--)
	{
		printf("%i\n", *array);
		++array;
	}
}


int main (int arg_count, char **arg_values)
{
	int		*array;
	t_solve *solve_values;

	arg_values += 1;
	arg_count -= 1;

	array = make_int_array(arg_count, arg_values);
	ft_print_int_array(array, (size_t)arg_count);
	solve_values = solve_numbers_asc(array, arg_count);

	ft_print_int_array(solve_values->answer, solve_values->answer_depth);
	return (0);
}