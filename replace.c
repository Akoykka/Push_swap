/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akoykka <akoykka@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/23 17:52:15 by akoykka           #+#    #+#             */
/*   Updated: 2022/07/24 18:42:40 by akoykka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void get_longest_branch(t_mnode *tree, t_branch *branch, size_t depth)
{
	size_t i;

	i = 0;
	(branch->current)[depth] = *(int *)(tree->content);
	if (depth > branch->answer_depth) 
	{
		branch->answer_depth = depth;
		ft_memcpy(branch->answer, branch->current, sizeof(int) * (depth + 1));
	}
	while (tree->next_size > i)
	{
		get_longest_branch((tree->next)[i], branch, depth + 1);
		++i;
	}
}

int move_array_pointer_and_adjust_size(int *array, size_t size)
{
	size_t i;

	i = 0;
	while (i < size && array[i] >= array[0])
		++i;
	return (i);
}

void get_insert_point(t_mnode *mtree, t_insert *temp, size_t depth)
{
	size_t i;

	i = 0;
	if (!mtree)
	{
		return ;
	}
	if (temp->value < *(int *)(mtree->content))
		return ;
	if (temp->max_depth < depth || temp->max_depth == 0)
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

t_llist *solve_numbers(int *array, size_t size, int sort)
{
	size_t i;
	size_t forward = 0;
	t_mnode 	*mtree;
	t_branch	branch;

	mtree = NULL;
	ft_bzero(&branch, sizeof(t_branch));
	if (sort == DESCENDING)
		array = ft_invert_int_array(array, size); /// modification
	while (size)
	{
		i = 0;
		while (size > i)
		{
			if (array[i] >= array[0])
			{
				if	(mtree == NULL)
					mtree = ft_mnode_new(&array[i], sizeof(int));
				else
					add_to_tree(mtree, &array[i], sizeof(int));
			}
			++i;
		}
		get_longest_branch(mtree, &branch, 0);
		ft_mnode_destroy(&mtree);
		forward = move_array_pointer_and_adjust_size(array, size);
		array += forward;
		size -= forward;
	}
	if (sort == DESCENDING)
		return (make_list(branch.answer, branch.answer_depth + 1, DESCENDING));
	return (make_list(branch.answer, branch.answer_depth + 1, ASCENDING));
}
