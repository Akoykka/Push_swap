/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swapoldie.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akoykka <akoykka@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 11:32:46 by akoykka           #+#    #+#             */
/*   Updated: 2022/06/07 13:23:42 by akoykka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"


void	push_to_stack(t_stack *stack, char push_to)
{
	if (push_to == 'a' && stack->size_a && stack->size_b)
		increase_indexes_by_one(stack->array_a, stack->size_a);
	if (push_to == 'a' && stack->size_b)
	{
		(stack->array_a)[0] = (stack->array_b)[0];
		++(stack->size_a);
		--(stack->size_b);
		shrink_indexes_by_one(stack->array_b, stack->size_b);
	}

	if (push_to == 'b' && stack->size_b && stack->size_a)
		increase_indexes_by_one(stack->array_b, stack->size_b);
	if (push_to == 'b' && stack->size_a)
	{
		
		(stack->array_b)[0] = (stack->array_a)[0];
		++(stack->size_b);
		--(stack->size_a);
		shrink_indexes_by_one(stack->array_a, stack->size_a);
	}
}

void	swap_top(t_stack *stack, char swap_stack)
{
	int	temp;

	if (swap_stack == 'a' && stack->size_a > 1)
	{
		temp = *(stack->array_a);
		*(stack->array_a) = *((stack->array_a) + 1);
		*((stack->array_a) + 1) = temp;
	}

	if (swap_stack == 'b' && stack->size_b > 1)
	{
		temp = *(stack->array_b);
		*(stack->array_b) = *((stack->array_b) + 1);
		*((stack->array_b) + 1) = temp;
	}
}

void	rotate_up(t_stack *stacks, char rotate_stack)
{
	int temp;


	if (rotate_stack == 'a' && stacks->size_a > 1)
	{
		temp = (stacks->array_a)[0];
		ft_printf("%i\n", temp);
		shrink_indexes_by_one(stacks->array_a, stacks->size_a);
		(stacks->array_a)[stacks->size_a - 1] = temp;
	}

	if (rotate_stack == 'b' && stacks->size_a > 1)
	{
		temp = (stacks->array_b)[0];
		ft_printf("%i\n", temp);
		shrink_indexes_by_one(stacks->array_b, stacks->size_b);
		(stacks->array_b)[stacks->size_b - 1] = temp;
	}

}

/*

void	bubble_sort(t_stack *stacks)
{
	int highest_value;
	int lowest_value;

	highest_value = stacks->size_b + stacks->size_a - 1;
	lowest_value = stacks->size_b;

	while (!is_sorted(stacks))
	{
		if ((stacks->array_a)[0] > (stacks->array_a)[1]
			&& (stacks->array_a[0] != (highest_value)
			&& stacks->array_a[1] != lowest_value))
		{
			swap_top(stacks, 'a');
			ft_strcat("s", stacks->operations_a);
		}
		rotate_up(stacks, 'a');
		ft_strcat("r", stacks->operations_a);
	}
}

void	reverse_order_bubble_sort(t_stack *stacks)
{
	int highest_value;
	int lowest_value;

	highest_value = stacks->size_b + stacks->size_a - 1;
	lowest_value = stacks->size_b;

	while (!is_sorted_rev(stacks))
	{
		if ((stacks->array_b)[0] < (stacks->array_b)[1]
			&& ((stacks->array_b)[0] != highest_value
			&& (stacks->array_b)[1] != lowest_value))
		{
			swap_top(stacks, 'b');
			ft_strcat("s", stacks->operations_b);
		}
		rotate_up(stacks, 'b');
		ft_strcat("r", stacks->operations_b);
	}
}
*/
void split(t_stack* stacks)
{
	int pivot;

	pivot = stacks->size_a / 2; // half rounded down is better to push to b (less moving)
	while (stacks->size_a > pivot)
	{
		if ((stacks->array_a)[0] < pivot)
		{
			push_to_stack(stacks, 'b');
			ft_strcat(stacks->premoves, "pb\n");
		}
		else
		{
			rotate_up(stacks, 'a');
			ft_strcat(stacks->premoves, "ra\n");
		}
	}
}

t_stack *make_struct(int argc, char **argv)
{
	t_stack *fresh;
	char **parameters;
	char amount_of_params;
	int *array;

	parameters = &argv[1];
	amount_of_params = argc - 1;

	fresh = (t_stack *)ft_memalloc(sizeof(t_stack));
	array = char_array_to_int_array(amount_of_params, parameters);
	fresh->array_b = (int *)ft_memalloc(sizeof(int) * (amount_of_params));
	fresh->array_a = simplify_numbers(array, amount_of_params);
	fresh->size_a = amount_of_params;
	fresh->size_b = 0;

	return (fresh);
}

void	*ft_memove(void *dst, const void *src, size_t len)
{
	int	i;

	i = 0;
	if (!dst & !src)
		len = 0;
	if (dst < src)
	{
		while (len--)
		{
			((unsigned char *)dst)[i] = ((const unsigned char *)src)[i];
			++i;
		}
	}
	else
	{
		while (len--)
			((unsigned char *)dst)[len] = ((const unsigned char *)src)[len];
	}
	return (dst);
}
int main(int arg_count, char **arg_values)
{
	t_stack *stacks;
	
	if (arg_count == 1)
		ft_error();
	stacks = make_struct(arg_count, arg_values);
	
	ft_printf("Beginning: array A:\n");
	ft_print_array(stacks->array_a, stacks->size_a);

	shrink_indexes_by_one(stacks->array_a, (stacks->size_a));
	
	ft_printf("array A:\n");
	ft_print_array(stacks->array_a, stacks->size_a);
	ft_printf("array B:\n");
	ft_print_array(stacks->array_b, stacks->size_b);
	/*
	split(stacks);
	ft_printf("\n%s\n", stacks->premoves);
	ft_printf("array A after split:\n");
	ft_print_array(stacks->array_a, stacks->size_a + 2);
	ft_printf("array B:\n");
	ft_print_array(stacks->array_b, stacks->size_b + 2);
	
	//ensiksi ilman split/pivot
	bubblesort(stacks);
	optimize_operations(stacks);
	ft_strcpy(stacks->current_best_cmd, stacks->operations_a);
	stacks->current_best = count_newlines(stacks->current_best_cmd);
	
	
	// pivotin kanssa
	
	bubble_sort(stacks);
	bubblesort(stacks);
	reverse_order_bubblesort(stacks);
	merge_and_optimize_operations(stacks);
	*/
	// pickup and drop optimization 
	return (0);
}



/*
void solver(t_stack *stacks)
{
	int loop;
	int rotations;

	
	loop = stacks->size_a
	while (loop-- && stacks->operations < stacks->current_best)
	{
		is_sorted(stacks);
		rotations = 0;
		while (array[0] < array[1] && !is_sorted)
		{
			rotate(t_stacks);
			++rotations;
		}
		swap(stacks, a);
		if (rotations > size / 2) /// could be division by 3
		{
			rotations = stacks->size_a - rotations
			write_to_cmdline(stacks, "rra\n", rotations)
		}
		else
			write_to_cmdline(stacks, "ra\n", rotations);
		solver(stacks);
		undo_rotations(stacks, rotations); // peruutetaan mikali ei mennykkaa
		rotate(stacks);
	}
}




void recursive_solver(t_stack *stack)
{
	if(stack->current_best > stack->actions || stack->size_a < 2
	|| is_sorted(stack))
	{
		if(is_sorted(stack))
		{
			stack->current_best = stack->actions;
			ft_strcpy(current_best_cmd, cmdline);
		}
		return;
	}
	if ((stack->array_a)[0] > (stack->array_a)[1])
	{
		++(stack->actions);
		ft_strcat("sa\n", stack->cmdline);
		swap_values(stack, a);
		rotator(stack);
		remove_last("sa\n", stack->cmdline);
		--(stack->actions);
	}
}



void rotator(t_stack *stack)
{
	int loop = stack->size_a;
	int loop2 = stack->size_a;
	
	while (loop--)
	{	
	//rotate forwards
		rotate(stack);
		ft_strcat("ra\n", stack->cmdline);
		++(stack->actions);
		recursive_solver(stack);
		
	}
	//Rotate backwards
	while (loop2--)
    {
		rrotate(stack);
		ft_strcat("rra\n", stack->cmdline);
		recursive_solver(stack);
		remove_last("rra\n", stack->cmdline);
		rotate(stack);
		--(stack->actions);
	}
	remove_last("ra\n", stack->cmdline);
}

*/
