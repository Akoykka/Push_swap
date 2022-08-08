/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akoykka <akoykka@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 13:23:00 by akoykka           #+#    #+#             */
/*   Updated: 2022/08/08 21:59:42 by akoykka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int assign_chunk(float value, float size, float split)
{
	int chunk;

	chunk = value / size / split;
	return(chunk + 1);
}

void fill_sort_struct(t_sort *sort, int *array, int size, float split)
{
	int		*simplified;

	ft_memset(sort->moves, '\0', (sizeof(char) * 200000));
	simplified = simplify_numbers(array,size);
	//free(array);
	//array = NULL;
	if(!simplified)
		exit(1);
	sort->stack_a = make_list(simplified , size, split);
	free(simplified);
	simplified = NULL;
	if(!sort->stack_a)
		exit(1);
	sort->curr_chunk = 1 / split;
	printf("fill_sort chunk is %i\n", sort->curr_chunk);
}



///////
//// VALID START
///////

int is_only_numbers(char *str)
{
	if (*str == '-' && ft_strlen(str) > 1)
		++str;
	while (*str)
	{
		if (!ft_isdigit(*str))
		{
			printf("isonlynumbers failed\n");
			return(0);
		}
		++str;
	}
	return(1);
}

int is_bigger_than_max(char *str)
{
	if (ft_isdigit(*str))
	{
		if (ft_strlen(str) > 10)
		{
			printf("bigger than max failed(number was %s)\n ", str);
			return (1);
		}
		if (ft_strlen(str) == 10
			&& ft_strcmp(str, "2147483647") > 0)
		{
			printf("bigger than max failed(number was %s)\n ", str);
			return (1);
		}
	}
	return (0);
}

int is_smaller_than_min(char *str)
{
	if(*str == '-')
	{
		if (ft_strlen(str) > 11)
		{
			printf("smaller than min failed\n");
			return (1);
		}
		if (ft_strlen(str) == 11
			&& ft_strcmp(str, "-2147483648") > 0)
		{
			printf("smaller than min failed\n");
			return (1);
		}
	}
	return(0);
}

int is_dup(char **numbers, int index, int size)
{
	char *target;

	target = numbers[index];
	++index;
	while (size > index)
	{
		if (ft_strcmp(target, numbers[index]) == 0)
		{
			printf("isdup failed\n");
			return(1);
		}
		++index;
	}
	return (0);
}


int is_valid_input(char **input, int size)
{
	int i;

	i = 0;
	if(!input || !size)
		return(0);
	while(size > i)
	{	if (!is_only_numbers(input[i])
			|| is_bigger_than_max(input[i])
			|| is_smaller_than_min(input[i])
			|| is_dup(input, i, size))
			return(0);
		++i;
	}
	return(1);
}
//// VALID END
///////

t_llist	*char_array_to_llist(char **array, int size)
{
	t_llist	*head;
	t_llist	*new;
	int		i;

	head = NULL;
	i = 0;
	if (!is_valid_input(array, size))
	{
		printf("ERROR NOT VALID NUMBERS");
		return (NULL);
	}
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
	return(head);
}

int is_all_assigned(t_llist *list)
{
	while (list)
	{
		if (!list->chunk)
			return (0);
		list = list->next;
	}
	return (1);
}

t_llist *find_smallest(t_list *list)
{
	t_list* smallest;

	smallest = list;
	while(list)
	{
		if (smallest->content > list->content)
			smallest = list;
		list = list->next;
	}
	return(smallest);
}

t_llist *find_next_smallest(t_llist *list, int prev_value)
{
	t_llist *next_smallest;

	while (list && list->content < prev_value)
		list = list->next;
	next_smallest = list;
	while(list)
	{
		if (list->content < next_smallest->content
			&& list->content > prev_value)
			next_smallest = list;
		list = list->next;
	}
	return (next_smallest);
}


int assign(t_sort *sort, int n)
{
	int total;
	int chunk;
	
	total = llist_len(sort->stack_a);
	chunk = (float)n / (float)total / sort->split + 1;
	return (chunk);
}

void assign_chunks(t_sort *sort)
{
	int n;
	t_llist *current;

	n = 1;
	current = find_smallest(sort->stack_a);
	current->chunk = assign(sort, n);

	while (n < llist_len(sort->stack_a));
	{	
		++n;
		current = find_next_smallest(sort->stack_a, current->content);
		current->chunk = assign(sort, n);
	}
}

void reset_struct(t_sort *sort, int argc, char **argv)
{
	char	**temp;

	temp = NULL;
	if (argc == 1)
	{
		ft_strsplit(*argv, ' ');
		sort->stack_a = char_array_to_llist(temp, get_len(temp));
		free_array(temp);
		temp = NULL;
	}
	else
		sort->stack_a = char_array_to_llist(argv, argc);
	if (!sort->stack_a)
		ft_error();
	assign_chunks(sort);
}

float adjust_split(void)
{
	static int	counter = 1;

	++counter;
	return(1.0f / counter);
}

int get_travel_a(t_sort *sort, int value, int direction)
{
	int travel_dist;
	t_llist *temp;

	temp = sort->stack_a;
	travel_dist = 0;
	while(temp->content != value)
	{
		++travel_dist;
		temp = temp->next;
	}
	if (direction == BACKWARD && travel_dist > 0)
		return (llist_len(sort->stack_a) - travel_dist);
	return (travel_dist);
}

int distance(t_sort *sort, int travel, int direction)
{
	if (direction == BACKWARD && travel)
		return(llist_len(sort->stack_b) - travel);
	return (travel);
}

int get_travel_b(t_sort *sort, int value, int direction)
{
	int travel_dist;
	t_llist *temp;

	temp = sort->stack_b;
	travel_dist = 0;
	if (llist_len(temp) < 1)
		return(0);
	while(temp)
	{
		if (is_biggest(sort, temp->content)
			&& (temp->content < value || is_smallest(sort, value)))
		{
			return(distance(sort, travel_dist, direction));
		}
		if (value < temp->content
			&& (!temp->next ||  value > temp->next->content))
		{
			return(distance(sort, travel_dist + 1, direction));
		}
		temp = temp->next;
		++travel_dist;
	}
	print_list(sort->stack_b);
	printf("stack_b is above the value is %i\n", value);
	printf("hit and miss value didnt fulfill parameters\n");
	exit(1);
}

void get_next_target(t_sort *sort)
{
	t_optim optimum;
	t_llist *temp;

	temp = sort->stack_a;
	while (temp)
	{
		if (temp->chunk == sort->curr_chunk)
		{
			optimum.forward_a = get_travel_a(sort, temp->content, FORWARD);
			optimum.forward_b = get_travel_b(sort, temp->content, FORWARD);
			optimum.backward_a = get_travel_a(sort, temp->content, BACKWARD);
			optimum.backward_b = get_travel_b(sort, temp->content, BACKWARD);
			compare_results(&optimum, temp->content);
		}
		temp = temp->next;
	}
	sort->curr_target = optimum.best_target;
	sort->direction = optimum.direction;
	sort->a_rotation = optimum.best_a;
	sort->b_rotation = optimum.best_b;
}

int is_curr_chunk_sorted(t_sort *sort, int curr_chunk)
{
	t_llist *temp;

	temp = sort->stack_a;
	while(temp)
	{
		if (temp->chunk == sort->curr_chunk)
			return (0);
		temp = temp->next;
	}
	return (1);
}

void sort_integers(t_sort *sort)
{
	int curr_chunk;

	curr_chunk = llist_len(sort->stack_a) / sort->split; 
	while(!curr_chunk)
	{
		while(!is_curr_chunk_sorted(sort, curr_chunk))
		{
			get_next_target(sort);
			move_target_to_stack_b(sort);
		}
		--curr_chunk;
	}
	align_biggest_number(sort);
	while(sort->stack_b)
	{
		push_stack(sort, STACK_B);
	}
}

int main(int arg_count, char **arg_values)
{
	t_sort sort;

	arg_count -= 1;
	arg_values += 1;

	sort.split = 1.0;
	while ((1.0f / 12.0f) < sort.split)
	{
		reset_struct(&sort, arg_count, arg_values);
		sort_integers();
		if (sort.current_best == NULL 
	 		|| llist_len(sort.moves) < llist_len(sort.current_best))
		{
			llist_destroy(sort.current_best);
			sort.current_best = sort.moves;
			sort.moves = NULL;
		}
		else
			llist_destroy(sort.moves);
		llist_destroy(sort.stack_a);
		llist_destroy(sort.stack_b);
		sort.split = adjust_split();
	}
}








int main (int arg_count, char **arg_values)
{
	int		*array;
	t_sort	sort;
	float	split;
	char	answer[2000000];

	arg_values += 1;
	arg_count -= 1;

	int x;
	x = 11;
	array = make_int_array(arg_count, arg_values);
	if (!array)
		exit(1);
	while(x--)
	{
		split = set_split(arg_count);
		fill_sort_struct(&sort, array, arg_count, split);
		sort_integers(&sort);
		printf("split is %f\t", split);
		printf("moves = %i\n", count_moves(sort.moves));
		if (!count_moves(answer) ||
			count_moves(sort.moves) < count_moves(answer))
		{
			ft_memcpy(answer, sort.moves, sizeof(char) * 200000);
			printf("found solution with %f split\n moves :%i\n", split, count_moves(answer));
		}
	}
	//llist_destroy(&(sort.stack_a));



	//printf("stack_a is:(%zu members)\n", llist_len(sort.stack_a));
	//print_list(sort.stack_a);
	//printf("stack_b is:(%zu members)\n", llist_len(sort.stack_b));
	//print_list(sort.stack_b);
	printf("final answer is\n");
	print_move_count(answer);
	//count_ra(sort, sort->moves);
	//printf("%s", sort->moves);
	return(0);
}