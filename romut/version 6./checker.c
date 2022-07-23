/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akoykka <akoykka@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 11:28:26 by akoykka           #+#    #+#             */
/*   Updated: 2022/06/05 20:55:39 by akoykka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker.h"

int	is_only_numbers(char *str)
{

	while (*str)
	{
		if (*str >= '9' && *str <= '0')
			return (0);
		++str;
	}
	return (1);
}

int	*char_array_to_int_array(int argc, char **argv)
{
	int	*stack;
	int	i;
	int	a_i;

	a_i = 0;
	i = 1;
	stack = (int *)malloc(sizeof(int) * (argc - 1));
	while (argc != i)
	{
		stack[a_i] = atoi(argv[i]);
		++i;
		++a_i;
	}
	return (stack);
}

int	is_valid_input(int argc, char **argv)
{
	int	input_i;
	int	i;

	i = 0;
	input_i = 1;
	while (input_i < argc)
	{
		if (!is_only_numbers(argv[input_i])
			|| atoi(argv[input_i]) > MAXIM_INT
			|| atoi(argv[input_i]) < MINIM_INT)
			return (0);
		++input_i;
	}
	return (1);
}

int is_cmd_valid(char *input)
{
	if (!ft_strcmp (input, "pa") || !ft_strcmp(input, "pb") || !ft_strcmp(input, "sa") 
	|| !ft_strcmp(input, "sb") || !ft_strcmp(input, "ss") || !ft_strcmp(input, "ra") 
	|| !ft_strcmp(input, "rb") || !ft_strcmp(input, "rr") || !ft_strcmp(input, "rra")
	|| !ft_strcmp(input, "rrb") || !ft_strcmp(input, "rrr"))
		return (1);
	return (0);
}

void	rotate_up(t_stack *stack, char stack_id)
{
	int	temp;

	if ((stack_id == 'a' || stack_id == 'r') && stack->size_a > 1)
	{
		temp = *(stack->array_a);
		ft_memmove(stack->array_a, stack->array_a + 1, stack->size_a - 1);
		(stack->array_a)[stack->size_a - 1] = temp;
	}
	if ((stack_id == 'b' || stack_id == 'r') && stack->size_b > 1)
	{
		temp = *(stack->array_b);
		ft_memmove(stack->array_b, stack->array_b + 1, stack->size_b - 1);
		(stack->array_b)[stack->size_b - 1] = temp;
	}
}

void	rrotate_down(t_stack *stack, char stack_id)
{
	int	temp;

	if ((stack_id == 'a' || stack_id == 'r') && stack->size_a > 1)
	{	
		temp = (stack->array_a)[stack->size_a - 1];
		ft_memmove(stack->array_a + 1, stack->array_a, stack->size_a - 1);
		*(stack->array_a) = temp;
	}
	if ((stack_id == 'b' || stack_id == 'r') && stack->size_b > 1)
	{	
		temp = (stack->array_b)[stack->size_b - 1];
		ft_memmove(stack->array_b + 1, stack->array_b, stack->size_b - 1);
		*(stack->array_b) = temp;
	}
}

void	swap_top(t_stack *stack, char stack_id)
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
		ft_memmove(stack->array_a + 1, stack->array_a, stack->size_a);
	if (stack_id == 'a' && stack->size_b)
	{
		*(stack->array_a) = *(stack->array_b);
		++(stack->size_a);
		--(stack->size_b);
		ft_memmove(stack->array_b, stack->array_b + 1, stack->size_b);
	}

	if (stack_id == 'b' && stack->size_b && stack->size_a)
		ft_memmove(stack->array_b + 1, stack->array_b, stack->size_b);
	if (stack_id == 'b' && stack->size_a)
	{
		*(stack->array_b) = *(stack->array_a);
		++(stack->size_b);
		--(stack->size_a);
		ft_memmove(stack->array_a, stack->array_a + 1, stack->size_a);
	}
}
void	operations(t_stack *stack, char *input)
{
	if (!is_cmd_valid(input))
		exit (1);
	if (strlen(input) == 3)
		rrotate_down(stack, input[2]);
	if (*input == 'p')
		push_to_stack(stack, input[1]);
	if (*input == 's')
		swap_top(stack, input[1]);
	if (*input == 'r')
		rotate_up(stack, input[1]);
}

void is_sorted(t_stack *stacks)
{
	int i;
	int loop;

	i = 0;
	loop = stacks->size_a - 1;
	while (loop--)
	{
		if ((stacks->array_a)[i] > (stacks->array_a)[i + 1])
		{
			printf("not in order");
			return ;
		}
		++i;
	}
	printf("in order, good job");
	return ;
}

void	execute_instructions(t_stack *stacks, char *string)
{
	int	i;
	char	**instructions;

	i = 0;
	instructions = ft_strsplit(string, ' ');
	while (instructions[i])
	{
		operations(stacks, instructions[i]);
		++i;
	}
}

char *get_sorting_instructions(void)
{
	int i;
	char *return_value;
	char buf[10000];
	char *instructions;
	int read_bytes;

	ft_memset(instructions, '\0', 10000);
	ft_memset(buf, '\0', 10000);
	read_bytes = read(0, &buf, 10000);
	
	instructions = ft_strndup(buf, read_bytes);
	ft_printf("buffer === |%s|",buf);
	ft_printf("read_bytes %i instructions === |%s|", read_bytes, instructions);
	return (instructions);
}


int	main(int argc, char **argv)
{
	t_stack	*stacks;
	int		loop;
	char	*instructions;

	loop = 0;
	if (!is_valid_input(argc, argv) || argc == 1)
		return (1);
	stacks = (t_stack *)malloc(sizeof(t_stack));
	stacks->array_b = (int *)malloc(sizeof(int) * (argc - 1));
	stacks->array_a = char_array_to_int_array(argc, argv);
	stacks->size_a = argc - 1;
	stacks->size_b = 0;
	while (loop < (argc - 1))
	{
		printf("%d\n", stacks->array_a[loop]);
		++loop;
	}
	instructions = get_sorting_instructions();
	execute_instructions(stacks, instructions);
	is_sorted(stacks);
	return (0);
}

