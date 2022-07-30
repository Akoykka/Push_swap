/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akoykka <akoykka@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 13:23:00 by akoykka           #+#    #+#             */
/*   Updated: 2022/07/31 00:33:54 by akoykka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void llist_rev(t_llist **head)
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

t_llist *llist_new(int content)
{
	t_llist *new;

	new = (t_llist *)ft_memalloc(sizeof(t_llist));
	if(!new)
		return NULL;

	new->content = content;
	new->next = NULL;
	new->chunk = 0;
	return(new);
}


void llist_add(t_llist **list, t_llist *new)
{
	new->next = *list;
	*list = new;
}

int assign_chunk(float value, float size, float split)
{
	int chunk;

	chunk = value / size / split;
	return(chunk + 1);
}

t_llist *make_list(int *array, int size, float split)
{
	t_llist *head;
	int i;

	head = NULL;
	i = 0;
	while (size > i)
	{
		llist_add(&head, llist_new(array[i]));
		if(!head)
			return NULL;
		head->chunk = assign_chunk(array[i], size, split);
		++i;
	}
	llist_rev(&head);
	return(head);
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



	//printf("stack_a is:(%zu members)\n", llist_len(sort.stack_a));
	//print_list(sort.stack_a);
	//printf("stack_b is:(%zu members)\n", llist_len(sort.stack_b));
	//print_list(sort.stack_b);
	printf("final answer is\n");
	print_move_count(answer);
	//count_ra(sort, sort->moves);
	//printf("%s", sort->moves);
}



/*
	ok ensiksi jaetaan numerot prosentuaalisesti osiin mikali
	parametrimaara ylittyy

	teen ensiksi isommilla numeroilla toimivan sortin


	jaetaan numerot viiteen osaan structissa type muutetaan chunk 1 2 3 jne

	end condition on kun chunkit loppuu.

	ensiksi kerataan chunk 1 stack b
	verrataan actioneiden maaraa seuraavaan kokojarjestyksessa olevaan numeroon
	tai seuraavaan samassa chunkissa olevaan.

	kun kaikki numerot ovat keratty b-stackiin
	siirrytaan chunk 2 jne,




	miten saadaan lista numeroista

	tehdaan niin etta muutetaan numerot kokojarjestykseen
*/