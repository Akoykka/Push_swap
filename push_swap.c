/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akoykka <akoykka@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 13:23:00 by akoykka           #+#    #+#             */
/*   Updated: 2022/07/15 19:26:14 by akoykka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void print_list(t_list *list)
{	if (!list)
		printf("EMPTY LIST\n");
	while(list)
	{
		ft_putnbr(*(int *)list->content);
		printf("\n");
		list = list->next;
	}
}

t_list *int_arr_to_list(int *array, size_t size)
{
	size_t	i;
	t_list	*fresh;

	fresh = NULL;
	i = 0;
	while (i < size)
	{
		if (fresh == NULL)
			fresh = ft_lst_new(&array[i], sizeof(int));
		else 
			ft_lst_add(&fresh, ft_lst_new(&array[i], sizeof(int)));
		++i;
	}
	ft_lst_reverse(&fresh);

	return (fresh);
}

void ft_del(void *target, size_t size)
{
	if(!target)
		return;
	ft_memset(target, 0, size);
	free(target);
	target = NULL;
}


t_list *ft_lst_dup_except(t_list *dup, t_list *except)
{
	t_list *temp;
	t_list *fresh;

	fresh = NULL;
	while(dup)
	{
		temp = except;
		while (temp && *(int *)dup->content != *(int *)temp->content)
			temp = temp->next;
		if (!temp)
			ft_lst_add(&fresh, ft_lst_new(dup->content, dup->content_size));
		dup = dup->next;
	}
	ft_lst_reverse(&fresh);
	return (fresh);
}


int *ft_invert_int_array(int *array, size_t size)
{
	size_t	high;
	size_t	low;
	int		temp;

	if (!array || !size)
		return 0;
	high = size - 1;
	low = 0;
	while(high > low)
	{
		temp = array[high];
		array[high] = array[low];
		array[low] = temp;
		--high;
		++low;
	}
	return (array);
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

int *make_int_array(int arg_count, char **arg_values)
{
	int	i;
	int *array;

	i = 0;
	array = (int *)ft_memalloc(sizeof(int) * arg_count);
	while (arg_count > i)
	{
		array[i] = ft_atoi(arg_values[i]);
		++i;
	}
	return(array);
}

t_sort *make_sort_struct(int *array, size_t size)
{
		t_sort *new;

		new = NULL;
		new = (t_sort *)ft_memalloc(sizeof(t_sort));
		new->stack_a = int_arr_to_list(array, size);
		new->solved = solve_numbers(array, size, ASCENDING);
		new->unsolved = ft_lst_dup_except(new->stack_a, new->solved);
		return (new);
}

int main (int arg_count, char **arg_values)
{
	int		*array;
	t_sort	*sort;

	arg_values += 1;
	arg_count -= 1;

	array = make_int_array(arg_count, arg_values);
	sort = make_sort_struct(array, arg_count);
	
	answersfive(sort);



	return (0);
}

/*
printf("unsolved len = %zu\n", ft_lst_count(sort->unsolved));
	printf("solved len = %zu\n", ft_lst_count(sort->solved));
	printf("stack_a len = %zu\n", ft_lst_count(sort->stack_a));
	printf("stack_b len = %zu\n", ft_lst_count(sort->stack_b));
	printf("asc len = %zu\n", ft_lst_count(sort->asc));
	printf("desc len = %zu\n", ft_lst_count(sort->desc));
unsolved len = 84
solved len = 16
stack_a len = 100
stack_b len = 0
asc len = 0
desc len = 0


static int	ft_whtspc(char c)
{
	if ((c <= 13 && c >= 9) || c == 32)
		return (1);
	return (0);
}

int	custom_atoi(const char *str)
{
	int	i;
	int	a;
	int	negative;

	negative = 1;
	a = 0;
	i = 0;
	while (ft_whtspc(str[i]) == 1)
		++i;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
		{
			negative = -1;
		}
		++i;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{	
		a = a * 10 + (str[i] - '0');
		++i;
	}
	return (a * negative);
}



char **check_input(int arg_count, char **arg_values)
{
	///is_only_numbers_and_spaces
	/// count spaces


	/// miten tietaa onko inputissa useampi luku
	

	/// miten tarkistaa onko kaikki lukuja ja valilla int_min int_max
		

	// is_duplicates

	/// lopulta muokkaus muotoon char **array

	
}


Muita charectereita kuin numeroita ja valeja

esim &^%@ tab tai aakkosia inputissa

Samoja numeroita

esim 33 11 02 33 11

isompia numeroita kuin max int tai pienempia kuin min int 

esim -3123123123 38 99 04 11233 1233983833838383 20 99


useita argumentteja yhdessa 

esim: "2 33 4 22 9" "3" "2 4 5 6"


*/
