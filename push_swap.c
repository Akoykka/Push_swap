/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akoykka <akoykka@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 13:23:00 by akoykka           #+#    #+#             */
/*   Updated: 2022/07/26 16:44:23 by akoykka          ###   ########.fr       */
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

t_llist *llist_new(int content, int chunk)
{
	t_llist *new;

	new = (t_llist *)ft_memalloc(sizeof(t_llist));
	if(!new)
		return NULL;

	new->content = content;
	new->next = NULL;
	new->chunk = chunk;
	return(new);
}


void llist_add(t_llist **list, t_llist *new)
{
	new->next = *list;
	*list = new;
}

int assign_chunk(int value, int size_of_stack)
{
	int chunk;
	
	chunk = value / size_of_stack;

}

t_llist *make_list(int *array, int size)
{
	t_llist *head;
	int i;

	head = NULL;
	i = 0;

	while (size > i)
	{
		llist_add(&head, llist_new(array[i], assign_chunk(array[i], size)));
		++i;
	}
	llist_rev(&head);
	return(head);
}


t_sort *make_sort_struct(int *array, int size)
{
	t_sort *sort;

	sort = (t_sort *)ft_memalloc(sizeof(t_sort));
	if (!sort)
		exit(1);
	
	sort->stack_a = make_list(simplify(array),size);
	return(sort);
}



int get_nbr_index_in_ascending_order(int base, int *array, int size, int n)
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
	return (get_nbr_index_in_ascending_order(base, array, size, (n - 1)));
}


int *simplify_numbers (int *array, int size)
{
	int *new;
	int n;

	new = (int *)malloc(sizeof(int) * (size));
	n = 0;
	while(n != size)
	{
		new[get_nbr_index_in_ascending_order(-2147483648, array, size, n)] = n;
		++n;
	}	
	return(new);
}



int main (int arg_count, char **arg_values)
{
	int		*array;
	t_sort	*sort;

	arg_values += 1;
	arg_count -= 1;

	array = make_int_array(arg_count, arg_values);
	sort = make_sort_struct(array, arg_count);
	

	//printf("stack_a is:(%zu members)\n", llist_len(sort->stack_a));
	//print_list(sort->stack_a);
	//printf("stack_b is:(%zu members)\n", llist_len(sort->stack_b));
	//print_list(sort->stack_b);
	//printf("SOLVED (%zu members)\n", llist_len(sort->solved));
	//print_list(sort->solved);
	//printf("UNSOLVED (%zu members)\n", llist_len(sort->unsolved));
	//print_list(sort->unsolved);
	//count_moves(sort->moves);
	//count_ra(sort, sort->moves);
	//printf("%s", sort->moves);
}
	



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
