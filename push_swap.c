/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akoykka <akoykka@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 13:23:00 by akoykka           #+#    #+#             */
/*   Updated: 2022/08/06 16:29:35 by akoykka          ###   ########.fr       */
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

float set_split(int arg_count)
{
	static int counter;

	++counter;
	printf("set split is %f\n", 1.0f / counter);
	return(1.0f / counter);
}


int main (int arg_count, char **arg_values)
{
	int		*array;
	t_sort	sort;
	float	split;
	char	answer[2000000];

	arg_values += 1;
	arg_count -= 1;

	int x;;
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
	llist_destroy(&(sort.stack_a));



	//printf("stack_a is:(%zu members)\n", llist_len(sort.stack_a));
	//print_list(sort.stack_a);
	//printf("stack_b is:(%zu members)\n", llist_len(sort.stack_b));
	//print_list(sort.stack_b);
	printf("final answer is\n");
	print_move_count(answer);
	//count_ra(sort, sort->moves);
	//printf("%s", sort->moves);
}