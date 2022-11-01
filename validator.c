/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validator.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akoykka <akoykka@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/13 17:11:12 by akoykka           #+#    #+#             */
/*   Updated: 2022/08/14 21:08:12 by akoykka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	is_only_numbers(char *str)
{
	if (*str == '-' && ft_strlen(str) > 1)
		++str;
	while (*str)
	{
		if (!ft_isdigit(*str))
		{
			return (0);
		}
		++str;
	}
	return (1);
}

int	is_bigger_than_max(char *str)
{
	if (ft_isdigit(*str))
	{
		if (ft_strlen(str) > 10 || (ft_strlen(str) == 10
				&& ft_strcmp(str, "2147483647") > 0))
		{
			return (1);
		}
	}
	return (0);
}

int	is_smaller_than_min(char *str)
{
	if (*str == '-')
	{
		if (ft_strlen(str) > 11 || (ft_strlen(str) == 11
				&& ft_strcmp(str, "-2147483648") > 0))
		{
			return (1);
		}
	}
	return (0);
}

int	is_dup(char **numbers, int index, int size)
{
	char	*target;

	target = numbers[index];
	++index;
	while (size > index)
	{
		if (ft_strcmp(target, numbers[index]) == 0)
		{
			return (1);
		}
		++index;
	}
	return (0);
}

int	is_valid_input(char **input, int size)
{
	int	i;

	i = 0;
	if (!input || !size)
		return (0);
	while (size > i)
	{	
		if (!is_only_numbers(input[i])
			|| is_bigger_than_max(input[i])
			|| is_smaller_than_min(input[i])
			|| is_dup(input, i, size))
			return (0);
		++i;
	}
	return (1);
}
