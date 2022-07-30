/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akoykka <akoykka@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/29 10:51:25 by akoykka           #+#    #+#             */
/*   Updated: 2022/07/30 15:06:58 by akoykka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void count_ra(t_sort *sort, char *str)
{
	char **moves;
	int amount_of_nodes;
	int counter = 0;
	int extra_moves = 0;
	int total_amount = 0;

	amount_of_nodes = llist_len(sort->stack_a);
	moves = ft_strsplit(str, '\n');

	while(*moves)
	{
		counter = 0;
		while (!strcmp(*moves, "ra"))
		{
			++moves;
			++counter;
			++total_amount;
		}
		if (counter > amount_of_nodes / 2)
		{
			extra_moves += counter - (amount_of_nodes / 2);
			printf("this many rotates %i\n ", counter);
		}
		++moves;
	}

	printf("There is total of %i of rotate_a\n", total_amount);
	printf("There is %i extra_moves of rotate \n", extra_moves);
}


void ft_print_int_array(int *array, size_t size)
{
	size_t i;

	i = 0;
	while (size > i)
	{
		printf("%i\n", *array);
		++array;
		++i;
	}
}


void print_list(t_llist *list)
{
	if (!list)
		printf("EMPTY LIST\n");
	while(list)
	{
		ft_putnbr(list->content);
		printf("\t\t (Chunk: %i)", list->chunk);
		printf("\n");
		list = list->next;
	}
}

void print_move_count(char *str)
{
	int moves;

	moves = 0;
	while(*str)
	{
		if (*str == '\n')
			++moves;
		++str;
	}
	printf("move amount is approx: %i\n", moves);
}

int count_moves(char *str)
{
	int moves;

	moves = 0;
	while(*str)
	{
		if (*str == '\n')
			++moves;
		++str;
	}
	return(moves);
}