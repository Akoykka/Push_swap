/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akoykka <akoykka@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 10:09:42 by akoykka           #+#    #+#             */
/*   Updated: 2022/06/17 13:10:16 by akoykka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

	t_list *make_list(char **array, int size)
	{
		t_list *head = NULL;
		t_list *new;
		int number;
		int i;

		i = 0;

		while(i < size)
		{
			number = ft_atoi(array[i]);
			new = ft_lst_new(&number, 4);
			ft_lst_add(&head, new);
			++i;
		}
		ft_lst_reverse(&head);
		return (head);
	}


	t_stack *make_struct(int arg_count, char **argv)
	{
		t_stack *stacks;
		t_list *head_array_a;

		stacks = (t_stack *)ft_memalloc(sizeof(t_stack));
		stacks->head_a = make_list(argv, arg_count);

		////
		printf("Print list: head_a\n");
		print_list(stacks->head_a);
		printf("Length of list is: %zu\n", ft_lst_count(stacks->head_a));
		/////

		stacks->head_b = NULL;
		stacks->size_a = arg_count;
		stacks->size_b = 0;
		ft_memset(stacks->operations_a, '\0', 50000);
		ft_memset(stacks->operations_b, '\0', 50000);
		return (stacks);
	}

void ft_mnode_insert(t_mnode *dst, t_mnode *new_mnode)
{
	int 	i;
	t_mnode **new_next;

	i = 0;
	new_next = (t_mnode **)ft_memalloc(sizeof(t_mnode *) * dst->next_size + 1);

	while (i < (dst->next_size))
	{
		new_next[i] = (dst->next)[i];
		++i;
	}
	(dst->next)[i] = new_mnode;
	++(dst->next_size);
}

void ft_mnode_destroy(t_mnode *root)
{
	if (!root)
		return ;

	while((root->next_size)--)
	{
		ft_mnode_destroy(*(root->next));
		++(root->next);
	}
	if (root->content)
	{
		free(root->content);
		root->content = NULL;
	}
	free(root);
	root = NULL;
}


t_mnode *ft_mnode_new(void const *content, size_t content_size)
{
	t_mnode *fresh;

	fresh = (t_mnode *)malloc(sizeof(t_mnode));
	if (!fresh)
		return (NULL);
	fresh->next_size = 0;
	fresh->content_size = 0;
	fresh->content = NULL;
	fresh->next = NULL;
	if (content)
	{
		fresh->content = (void *)malloc(content_size);
		if (!fresh->content)
		{
			free(fresh);
			return (NULL);
		}
		ft_memcpy(fresh->content, content, content_size);
		fresh->content_size = content_size;
	}
	return (fresh);
}

t_list make_list(t_list *stack_a)
{
	void *value;
	temp *t_list;

	while(stack_a)
	{
		temp = stack_a
		value = stack_a->content



	}



}






int main(int arg_count, char **arg_values)
{
	t_stack *stacks;
	t_list *optimal_asc;

	arg_values += 1;
	arg_count -= 1;
	if (arg_count == 0)
		ft_error();
	stacks = make_struct(arg_count, arg_values);


	return (0);
}
