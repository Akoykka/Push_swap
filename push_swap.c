/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akoykka <akoykka@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 10:09:42 by akoykka           #+#    #+#             */
/*   Updated: 2022/06/21 14:42:30 by akoykka          ###   ########.fr       */
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
	t_mnode **new_next_index;

	i = 0;
	new_next_index = (t_mnode **)ft_memalloc(sizeof(t_mnode *) * (dst->next_size + 1));

	while (i < (dst->next_size))
	{
		new_next_index[i] = (dst->next)[i];
		++i;
	}
	(new_next_index)[i] = new_mnode;
	++(dst->next_size);
	//free old dst->next
	dst->next = new_next_index;
}

void ft_mnode_destroy(t_mnode **root)
{
	size_t i;

	i = 0;
	if (!root || !*root)
		return ;
	while(i < (*root)->next_size)
	{
		ft_mnode_destroy(&((*root)->next)[i]);
		++i;
	}
	if ((*root)->content != NULL)
	{
		ft_memdel(&((*root)->content));
	}
	ft_memdel((void *)root);
}


t_mnode *ft_mnode_new(void const *content, size_t content_size)
{
	t_mnode *fresh;

	fresh = (t_mnode *)ft_memalloc(sizeof(t_mnode));
	if (!fresh)
		return (NULL);
	fresh->next_size = 0;
	fresh->content_size = 0;
	fresh->content = NULL;
	fresh->next = NULL;
	if (content != NULL)
	{
		fresh->content = (void *)ft_memalloc(content_size);
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


void print_input(void *content)
{
	int result;

	result = *(int *)content;

	printf("INPUT IS %d\n", result);


}






void print_mnode(t_mnode *head)
{
	int i;

	i = 0;
	if(!head)
	{
		printf("nothing found\n");
		return ;
	}

	if (head->content != NULL)
		printf("print_mnode %d\n", *(int *)(head->content));

	printf("%zu indexes found:\n", head->next_size);
	while (i < head->next_size)
	{
		print_mnode((head->next)[i++]);
	}

}
void get_insert_point(t_mnode *head, int *value, int *depth, int curr_depth, t_mnode **point)
{
	size_t i;

	i = 0;
	if (!head || !head->content || !value || !depth)
		return ;

	if (*(int *)(head->content) > *value)
	{
		return ;
	}
	if (*depth < curr_depth)
	{
		*depth = curr_depth;
		head = *point;
	}
	while (head->next_size > i)
	{
		get_insert_point((head->next)[i], value, depth, curr_depth + 1, point);
		++i;
	}
}


void insert_to_mnode(t_mnode *head, t_mnode *new)
{
	int *depth;
	t_mnode *insert_point;

	insert_point = NULL;
	*depth = 0;
	get_insert_point(head, new->content, depth, 0, &insert_point);
	ft_mnode_insert(insert_point, new);
}

int get_depth(t_mnode *tree, int depth)
{
	size_t i; /// this makes no sense

	i = 0;
	while (tree->next_size > i)
	{
		depth = get_depth((tree->next)[i], depth + 1);
		++i;
	}
	return(depth);
}
t_list *find_n_cpy_longest_branch(t_mnode *tree)
{
	t_list *copy;
	int max_depth;

	copy = NULL;
	max_depth = get_depth(tree);





	return(copy)
}

t_list *get_longest_list(t_list *list)
{
	int start_value;
	t_mnode *temp;

	temp = NULL;
	start_value = *(int *)(list->content);

	while (list)
	{
		if (*(int *)(temp->content) >= start_value)
		{
			if (temp == NULL)
			{
				temp = ft_mnode_new(list->content, list->content_size);
			}
			else
			{
				insert_to_mnode(temp, ft_mnode_new(list->content, list->content_size));
			}
		}
		list = list->next;
	}
	//cpy_longest_depth(temp)
	//free everything
	return(temp);
}


t_list *make(t_list *temp)
{
	int low;
	t_list *longest_list;

	low = *(int *)(temp->content);

	while (temp)
	{
		if(temp->content && *(int *)(temp->content) <= low)
		{
			printf("contents are %i\n", *(int *)(temp->content));
			low = *(int *)(temp->content);
		}
		temp = temp->next;
	}
	printf("end of list\n");

	return (longest_list);
}





int main(int arg_count, char **arg_values)
{
	t_stack *stacks;
	t_list *optimal_asc;
	t_mnode *head;
	t_mnode *leg;

	arg_values += 1;
	arg_count -= 1;
	if (arg_count == 0)
		ft_error();
	int number = 9;
	stacks = make_struct(arg_count, arg_values);
	optimal_asc = make(stacks->head_a);
	head = ft_mnode_new((void *)&number, sizeof(int));
	number = 11;
	ft_mnode_insert(head, ft_mnode_new((void *)&number, sizeof(int)));
	ft_mnode_insert(head, ft_mnode_new((void *)&number, sizeof(int)));
	ft_mnode_insert(head, ft_mnode_new((void *)&number, sizeof(int)));

	print_mnode(head);
	ft_mnode_destroy(&head);
	print_mnode(head);
	return (0);
}
