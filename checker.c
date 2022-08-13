/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akoykka <akoykka@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/08 14:02:00 by akoykka           #+#    #+#             */
/*   Updated: 2022/08/13 18:19:36 by akoykka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker.h"

/////LLIST FUNCTIONS START
/////
/*
void llist_add(t_llist **list, t_llist *new)
{
	new->next = *list;
	*list = new;
}


void	llist_rev(t_llist **head)
{
	t_llist	*temp_prevnode;
	t_llist	*temp;
	t_llist	*temp_nextnode;

	temp_prevnode = NULL;
	temp_nextnode = NULL;
	if (!head || !*head)
		return ;
	temp = *head;
	while (temp)
	{
		temp_nextnode = temp->next;
		temp->next = temp_prevnode;
		temp_prevnode = temp;
		temp = temp_nextnode;
	}
	*head = temp_prevnode;
}

t_llist	*llist_new(int content)
{
	t_llist *new;

	new = (t_llist *)ft_memalloc(sizeof(t_llist));
	if(!new)
		return NULL;

	new->content = content;
	new->next = NULL;
	return(new);
}

size_t	llist_len(t_llist *list)
{
	size_t length;

	length = 0;
	while (list)
	{
		length++;
		list = list->next;
	}
	return (length);
}

void	llist_destroy(t_llist **list)
{
	t_llist *temp;
	t_llist *next;

	if(!list)
		return ;
	next = NULL;
	temp = *list;

	while(temp)
	{
		next = temp->next;
		free(temp);
		temp = next;
	}
	list = NULL;
}
*/
void	free_all(t_stacks *stacks)
{
	llist_destroy(&(stacks->stack_a));
	llist_destroy(&(stacks->stack_b));
	llist_destroy(&(stacks->moves));
}

void	ft_error(t_stacks *stacks)
{
	write(1, "Error", 6);
	free_all(stacks);
	exit (1);
}

t_llist	*char_array_to_llist(char **array, int size)
{
	t_llist	*head;
	t_llist	*new;
	int		i;

	head = NULL;
	i = 0;
	if (!is_valid_input(array, size))
		return (NULL);
	while (size > i)
	{
		new = llist_new(ft_atoi(array[i]));
		if (!new)
		{
			llist_destroy(&head);
			return (NULL);
		}
		llist_add(&head, new);
		++i;
	}
	llist_rev(&head);
	return (head);
}

int	get_len(char **array)
{
	int	i;

	i = 0;
	while (array[i])
		++i;
	return (i);
}

void	free_array(char **array)
{
	int	i;

	if (!array)
		return ;
	i = 0;
	while (array[i])
	{
		free(array[i]);
		array[i] = NULL;
		++i;
	}
	free(array[i]);
	free(array);
	array = NULL;
}

void	make_struct(int arg_count, char **arg_values, t_stacks *stacks)
{
	char	**temp;

	temp = NULL;
	if (arg_count == 1)
	{
		temp = ft_strsplit(*arg_values, ' ');
		stacks->stack_a = char_array_to_llist(temp, get_len(temp));
		free_array(temp);
		temp = NULL;
	}
	else
		stacks->stack_a = char_array_to_llist(arg_values, arg_count);
	if (!stacks->stack_a)
	{
		write(1, "Error\n", 6);
		exit (1);
	}
		stacks->stack_b = NULL;
}

int	parse_move(char *next_move)
{
	if (!ft_strcmp (next_move, "pa"))
		return (0);
	if (!ft_strcmp (next_move, "pb"))
		return (1);
	if (!ft_strcmp (next_move, "sa"))
		return (2);
	if (!ft_strcmp (next_move, "sb"))
		return (3);
	if (!ft_strcmp (next_move, "ss"))
		return (4);
	if (!ft_strcmp (next_move, "ra"))
		return (5);
	if (!ft_strcmp (next_move, "rb"))
		return (6);
	if (!ft_strcmp (next_move, "rr"))
		return (7);
	if (!ft_strcmp (next_move, "rra"))
		return (8);
	if (!ft_strcmp (next_move, "rrb"))
		return (9);
	if (!ft_strcmp (next_move, "rrr"))
		return (10);
	return (11);
}

void	get_moves(t_stacks *stacks)
{
	char	*next_move;
	int		ret;
	t_llist	*new;

	next_move = NULL;
	ret = get_next_line(0, &next_move);
	while (ret)
	{
		if (ret == -1)
		{
			write(1, "Error\n", 6);
			ft_error(stacks);
		}
		new = llist_new(parse_move(next_move));
		if (!new)
		{
			free(next_move);
			write(1, "Error\n", 6);
			ft_error(stacks);
		}
		llist_add(&stacks->moves, new);
		free(next_move);
		next_move = NULL;
		ret = get_next_line(0, &next_move);
	}
	llist_rev(&stacks->moves);
}
/////
//// MOVES START
/////

t_llist	*get_llist_tail(t_llist *list)
{
	while (list->next)
		list = list->next;
	return (list);
}

void	push_a(t_stacks *stacks)
{
	t_llist *target;

	if (stacks->stack_b)
	{
		target = stacks->stack_b;
		stacks->stack_b = stacks->stack_b->next;
		target->next = stacks->stack_a;
		stacks->stack_a = target;
	}
}

void	push_b(t_stacks *stacks)
{

	t_llist *target;

	if (stacks->stack_a)
	{
	target = stacks->stack_a;
	stacks->stack_a = stacks->stack_a->next;
	target->next = stacks->stack_b;
	stacks->stack_b = target;
	}
}



void	swap_a(t_stacks *stacks)
{
	t_llist *first;
	t_llist *second;

	if (llist_len(stacks->stack_a) > 1)
	{
		first = stacks->stack_a;
		second = stacks->stack_a->next;
		stacks->stack_a = second;
		first->next = second->next;
		second->next = first;
	}
}

void	swap_b(t_stacks *stacks)
{
	t_llist *first;
	t_llist *second;

	if (llist_len(stacks->stack_b) > 1)
	{
		first = stacks->stack_b;
		second = stacks->stack_b->next;
		stacks->stack_b = second;
		first->next = second->next;
		second->next = first;
	}
}

void	swap_both(t_stacks *stacks)
{
	swap_a(stacks);
	swap_b(stacks);
}

void	rotate_a(t_stacks *stacks)
{
	t_llist	*target;

	target = NULL;
	if (llist_len(stacks->stack_a) > 1)
	{
		target = stacks->stack_a;
		stacks->stack_a = stacks->stack_a->next;
		get_llist_tail(stacks->stack_a)->next = target;
		target->next = NULL;
	}
}

void	rotate_b(t_stacks *stacks)
{
	t_llist	*target;

	target = NULL;

	if (llist_len(stacks->stack_b) > 1)
	{
		target = stacks->stack_b;
		stacks->stack_b = stacks->stack_b->next;
		get_llist_tail(stacks->stack_b)->next = target;
		target->next = NULL;
	}
}

void	rotate_both(t_stacks *stacks)
{
	rotate_a(stacks);
	rotate_b(stacks);
}

void	rrotate_a(t_stacks *stacks)
{
	t_llist	*target;
	t_llist	*temp;

	temp = NULL;
	target = NULL;
	if (llist_len(stacks->stack_a) > 1)
	{
		target = get_llist_tail(stacks->stack_a);
		temp = stacks->stack_a;
		while (temp->next != target)
			temp = temp->next;
		temp->next = NULL;
		target->next = stacks->stack_a;
		stacks->stack_a = target;
	}
}

void	rrotate_b(t_stacks *stacks)
{
	t_llist	*target;
	t_llist	*temp;

	temp = NULL;
	target = NULL;
	if (llist_len(stacks->stack_b) > 1)
	{
		target = get_llist_tail(stacks->stack_b);
		temp = stacks->stack_b;
		while (temp->next != target)
			temp = temp->next;
		temp->next = NULL;
		target->next = stacks->stack_b;
		stacks->stack_b = target;
	}
}

void	rrotate_both(t_stacks *stacks)
{
	rrotate_a(stacks);
	rrotate_b(stacks);
}

void	is_error(t_stacks *stacks)
{
	write(1, "Error, parsing_error\n", 21);
	ft_error(stacks);
}

/////
//// MOVES END
//////

void	execute_moves(t_stacks *stacks)
{
	int				i;
	t_llist			*temp;
	static const	t_dispatch_table dispatch_table[12] = {
		push_a,
		push_b,
		swap_a,
		swap_b,
		swap_both,
		rotate_a,
		rotate_b,
		rotate_both,
		rrotate_a,
		rrotate_b,
		rrotate_both,
		is_error
	};

	temp = stacks->moves;
	i = 0;
	while (temp)
	{
		dispatch_table[temp->content](stacks);
		temp = temp->next;
	}
}

int	is_in_order(t_stacks *stacks)
{
	t_llist	*temp;

	temp = stacks->stack_a;
	if (stacks->stack_b == NULL)
	{
		while (temp->next)
		{
			if (temp->content > temp->next->content)
				return (0);
			temp = temp->next;
		}
		return (1);
	}
	return (0);
}

int	main(int arg_count, char **arg_values)
{
	t_stacks	stacks;

	arg_count--;
	arg_values++;
	make_struct(arg_count, arg_values, &stacks);
	get_moves(&stacks);
	execute_moves(&stacks);
	if (is_in_order(&stacks))
		write(1, "OK\n", 3);
	else
		write(1, "KO\n", 3);
	free_all(&stacks);
	return (0);
}
