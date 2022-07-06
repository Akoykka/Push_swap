/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swapv4.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akoykka <akoykka@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 10:09:42 by akoykka           #+#    #+#             */
/*   Updated: 2022/06/22 14:43:25 by akoykka          ###   ########.fr       */
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






void get_longest_branch(t_mnode *tree, t_cpy *temp, size_t depth)
{
	size_t i;

	i = 0;
	if (!tree || !temp)
		return;
	
	(temp->current)[depth] = *(int *)(tree->content);

	if (depth > temp->answer_depth)
	{
		temp->answer_depth = depth;
		ft_memcpy(temp->answer, temp->current, depth);
	}

	while (tree->next_size > i)
	{
		get_longest_branch((tree->next)[i], temp, depth + 1);
		++i;
	}
}

t_cpy *cpy_max_depth(t_mnode *tree)
{
	t_cpy *temp;
	
	temp = (t_cpy *)ft_memalloc(sizeof(t_cpy));

	get_longest_branch(tree, temp, 0);

	return(temp);
}

t_cpy *get_longest_list(t_list *list)
{
	int start_value;
	t_mnode *temp;
	t_cpy *new;

	temp = NULL;
	start_value = *(int *)(list->content);

	while (list)
	{
		if (*(int *)(temp->content) >= start_value)
		{
			if (temp == NULL)
				temp = ft_mnode_new(list->content, list->content_size);
			else
				insert_to_mnode(temp, ft_mnode_new(list->content, list->content_size));
		}
		list = list->next;
	}
	new = cpy_max_depth(temp);
	//free everything
	return(new); //// HERE FIX THIS
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
			get_longest_list(temp);
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



get values -> make int array 

get maxsize 

set ints in multitree 

get longest int array

make int array 

make int array into linked list = Solved numbers

set left out ints in multitree = To be solved numbers

set left out ints descending = To be solved numbers


How far can you go without linked list

make int array

make copy 

insert copy into mtree 

get longest possible straight

also do it again for second longest 

then do it DESCENDING

then turn those int arrays into linked lists

