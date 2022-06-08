/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jargon.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akoykka <akoykka@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 18:41:51 by akoykka           #+#    #+#             */
/*   Updated: 2022/06/07 17:16:19 by akoykka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
sa : swap a - swap the first 2 elements at the top of stack a. Do nothing if there
is only one or no elements).
sb : swap b - swap the first 2 elements at the top of stack b. Do nothing if there
is only one or no elements).
ss : sa and sb at the same time.
pa : push a - take the first element at the top of b and put it at the top of a. Do
nothing if b is empty.
pb : push b - take the first element at the top of a and put it at the top of b. Do
nothing if a is empty.
ra : rotate a - shift up all elements of stack a by 1. The first element becomes
the last one.
rb : rotate b - shift up all elements of stack b by 1. The first element becomes
the last one.
rr : ra and rb at the same time.
rra : reverse rotate a - shift down all elements of stack a by 1. The last element
becomes the first one.
8
Push_swap Because Swap_push isn’t as natural
rrb : reverse rotate b - shift down all elements of stack b by 1. The last element
becomes the first one.
rrr : rra and rrb at the same time.


swap_top_two
push_src_dest
shift_up_by_one
shift_down_by_one

pa	push_to_stack(stack & a)
pb	push_to_stack(stack & b)

sa 	swap_top(stack_a);
sb	swap_top(stack_b);
ss 	sa + sb

ra	rotate_up(stack_a);
rb	rotate_up(stack_b);
rr ra + rb

rra rrotate_down(stack_a);
rrb	rrotate_down(stack_b);
rrr	rra + rrb


#include <string.h>



/*
t_list *ft_lst_get_tail(t_list *head)
{
	if (!head)
		return (NULL);
	while(head->next)
		head = head->next;
	return (head);
}


void ft_lst_move_one_to_tail(t_list **head, t_list *target)
{
	t_list	*temp;

	temp = *head;
	if (*head == target)
		*head = temp->next;
	else
	{
		while(temp->next != target && temp->next)
			temp = temp->next;
		temp->next = target->next;
	}
	(ft_lst_get_tail(*head))->next = target;
	target->next = NULL;
}
*/
/*
void ft_lst_push_top(t_list **src, t_list **dest)
{
	t_list	*temp;
	
	if (!src || !dest)
		return;
	temp = *src;
	*src = (*src)->next;
	temp->next = *dest;
	*dest = temp;
}
*/
/*
void ft_lst_move_to_top(t_list **head, t_list *target)
{
	t_list	*temp;
	
	temp = *head;
	if (!head || *head == target)
		return;
	while (temp)
	{
		if (temp->next == target)
		{
			temp->next = target->next;
			target->next = *head;
			*head = target;
		}
		temp = temp->next;
	}
}
*/
/*
int get_index(int base, int *array, int size, int n)
{
	int temp;	
	int index;
	int i;

	temp = 2147483647;
	i = 0;
	
	while(size != i)
	{
		if(array[i] > base && array[i] <= temp)
		{
			index = i;
			temp = array[i];
		}
		++i;
	}
	if (n == 0)
		return(index);
	base = temp;
	return (get_index(base, array, size, (n - 1)));
}


int *simplify_numbers (int *array, int size)
{
	int *new;
	int n;

	new = (int *)malloc(sizeof(int) * (size));
	n = 0;
	while(n != size)
	{
		new[get_index(-2147483648, array, size, n)] = n;
		++n;
	}	
	return(new);
}
*/


int is_input_valid(char *input)
{
	if (strcmp (input, "pa") || strcmp (input, "pb") || strcmp (input, "sa") 
	|| strcmp (input, == "sb") || strcmp (input, == "ss") || strcmp (input, == "ra") 
	|| strcmp (input, == "rb") || strcmp (input, == "rr") || strcmp (input, == "rra")
	|| strcmp (input, == "rrb") strcmp (input, == "rrr"))
		return (1);
	return (0);
}

void	operations(t_stack *stack, char *input)
{
	if (!is_valid_input)
		exit ("not valid input");
	if (ft_strlen(input) == 3)
		rotate_down(stack, input[2]);
	if (*input == 'p')
		push_to_stack(stack, input[1]);
	if (*input == 's')
		swap_top(stack, input[1]);
	if (*input == 'r')
		rotate_up(stack, input[1]);
}

void	rotate_up(t_stack *stack, char stack_id)
{
	int	temp;

	if ((stack_id == 'a' || stack_id == 'r') && stack->size_a > 1)
	{
		temp = *(stack->array_a);
		memmove(stack->array_a, stack->array_a + 1, stack->size_a - 1);
		(stack->array_a)[stack->size_a - 1] = temp;
	}
	if ((stack_id == 'b' || stack_id == 'r') && stack->size_b > 1)
	{
		temp = *(stack->array_b);
		memmove(stack->array_b, stack->array_b + 1, stack->size_b - 1);
		(stack->array_b)[stack->size_b - 1] = temp;
	}
}

void	rrotate_down(t_stack *stack, char stack_id)
{
	int	temp;

	if ((stack_id == 'a' || stack_id == 'r') && stack->size_a > 1)
	{	
		temp = (stack->array_a)[stack->size_a - 1];
		memmove(stack->array_a + 1, stack->array_a, stack->size_a - 1);
		*(stack->array_a) = temp;
	}

	if ((stack_id == 'b' || stack_id == 'r') && stack->size_b > 1)
	{	
		temp = (stack->array_b)[stack->size_b - 1];
		memmove(stack->array_b + 1, stack->array_b, stack->size_b - 1);
		*(stack->array_b) = temp;
	}

}

void	swap_top(t_stack *stack char stack_id)
{
	int	temp;

	if ((stack_id == 'a' || stack_id == 's') && stack->size_a > 1)
	{
		temp = *(stack->array_a);
		*(stack->array_a) = *((stack->array_a) + 1);
		*((stack->array_a) + 1) = temp;
	}

	if ((stack_id == 'b' || stack_id == 's') && stack->size_b > 1)
	{
		temp = *(stack->array_b);
		*(stack->array_b) = *((stack->array_b) + 1);
		*((stack->array_b) + 1) = temp;
	}
}

void	push_to_stack(t_stack *stack, char stack_id)
{
	if (stack_id == 'a' && stack->size_a && stack->size_b)
		memmove(stack->array + 1, stack->array, stack->size);
	if (stack_id == 'a' stack->size_b)
	{
		*(stack->array_a) = *(stack->array_b);
		++(stack->size_a);
		--(stack->size_b);
	}

	if (stack_id == 'b' && stack->size_b && stack->size_a)
		memmove(stack->array + 1, stack->array, stack->size);
	if (stack_id == 'b' && stack->size_a)
	{
		*(stack->array_b) = *(stack->array_a);
		++(stack->size_b);
		--(stack->size_a);
	}
}



void	push_to_b(t_stack *stack  char stack_id)
{
	if (stack_id == 'b' && stack->size_b && stack->size_a)
		memmove(stack->array + 1, stack->array, stack->size);
	if (stack->size_a)
	{
		*(stack->array_b) = *(stack->array_a);
		++(stack->size_b);
		--(stack->size_a);
	}
}



void	push_top_dest_src(t_stack *dest, t_stack *source)
{
	if (stack->size && src->size)
	{
		memmove(stack->array + 1, stack->array, stack->size);
		*(dest->array) = *(source->array);
	}
}
*/

/*
void	rotate_up(t_stack *stack, char stack_id)
{
	int	temp;

	if ((stack_id == 'a' || stack_id == '2') && stack->size_a > 1)
	{
		temp = *(stack->array_a);
		ft_memmove(stack->array_a, stack->array_a + 1, stack->size_a - 1);
		(stack->array_a)[stack->size_a - 1] = temp;
	}
	if ((stack_id == 'b' || stack_id == '2') && stack->size_b > 1)
	{
		temp = *(stack->array_b);
		ft_memmove(stack->array_b, stack->array_b + 1, stack->size_b - 1);
		(stack->array_b)[stack->size_b - 1] = temp;
	}
}

void	rrotate_down(t_stack *stack, char stack_id)
{
	int	temp;

	if ((stack_id == 'a' || stack_id == '2') && stack->size_a > 1)
	{	
		temp = (stack->array_a)[stack->size_a - 1];
		ft_memmove(stack->array_a + 1, stack->array_a, stack->size_a - 1);
		*(stack->array_a) = temp;
	}

	if ((stack_id == 'b' || stack_id == '2') && stack->size_b > 1)
	{	
		temp = (stack->array_b)[stack->size_b - 1];
		ft_memmove(stack->array_b + 1, stack->array_b, stack->size_b - 1);
		*(stack->array_b) = temp;
	}

}

void	swap_top(t_stack *stack, char stack_id)
{
	int	temp;

	if ((stack_id == 'a' || stack_id == '2') && stack->size_a > 1)
	{
		temp = *(stack->array_a);
		*(stack->array_a) = *((stack->array_a) + 1);
		*((stack->array_a) + 1) = temp;
	}
	if ((stack_id == 'a' || stack_id == '2') && stack->size_b > 1)
	{
		temp = *(stack->array_b);
		*(stack->array_b) = *((stack->array_b) + 1);
		*((stack->array_b) + 1) = temp;
	}
}

void	push_to_stack(t_stack *stack, char stack_id)
{
	if (stack_id == 'a' && stack->size_a && stack->size_b)
		ft_memmove(stack->array + 1, stack->array, stack->size);
	if (stack_id == 'a' stack->size_b)
	{
		*(stack->array_a) = *(stack->array_b);
		++(stack->size_a);
		--(stack->size_b);
	}
	if (stack_id == 'b' && stack->size_b && stack->size_a)
		ft_memmove(stack->array + 1, stack->array, stack->size);
	if (stack_id == 'b' && stack->size_a)
	{
		*(stack->array_b) = *(stack->array_a);
		++(stack->size_b);
		--(stack->size_a);
	}
}
*/
