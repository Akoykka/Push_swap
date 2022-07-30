/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simplify.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akoykka <akoykka@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/29 10:42:22 by akoykka           #+#    #+#             */
/*   Updated: 2022/07/30 16:16:44 by akoykka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static int get_index(int base, int *array, int size, int n)
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
	if(!new)
		return (NULL);
	n = 0;
	while(n != size)
	{
		new[get_index(-2147483648, array, size, n)] = n;
		++n;
	}
	return(new);
}
