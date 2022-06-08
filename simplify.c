/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simplify.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akoykka <akoykka@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 13:24:09 by akoykka           #+#    #+#             */
/*   Updated: 2022/06/07 10:00:00 by akoykka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

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

/*  			Heres the main
int main(void)
{
	int array[] = {-22, 3, 77, 7, 5, 777, -333, 123, 0};
	int size_a = 9;
	int i = 0;
	int *new;
	while(size_a != i)
	{
		printf("start	: %d\n", array[i]);
		++i;
	}

	new = simplify_numbers(array, size_a);

	i = 0;
	while(size_a != i)
	{
		printf("end: %d\n", new[i]);
		++i;
	}
	return (0);
}

int get_lowest_val_index(int *array, int size)
{
	int lowest_value_index;
	int lowest_value;
	int i;

	i = 0;
	lowest_value = array[i];
	while(size != i)
	{
		if (lowest_value > array[i])
			lowest_value_index = i;
		++i;
	}
	return(lowest_value_index);
}

int get_nth_lowest_val_index(int *array, int size, int n)
{
	static int previous_low_index;
	int low_index;
	int i;

	i = 0;
	low_index = get_lowest_val_index(array, size);
	if (n)
	{
		while(array[i] < array[previous_low_index])
			++i;
		low_index = i;
		while(size != i)
		{
		if (array[low_index] > array[i])
			low_index = i;
		++i;
		}
	}
	previous_low_index = low_index;
	return(low_index);
}
*/