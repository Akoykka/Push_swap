/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akoykka <akoykka@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/10 20:03:59 by akoykka           #+#    #+#             */
/*   Updated: 2022/07/10 21:05:22 by akoykka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/includes/libft.h"

int	custom_atoi(const char *str)
{
	int	i;
	long long	a;
	int	negative;

	negative = 1;
	a = 0;
	i = 0;

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
	return(a < 2147483647 && a > 2147483648);
}

int is_only_numbers_and_spaces(char *str)
{
	int i;

	i = 0;
	while(str[i])
	{
		if (str[i] != 32 || !ft_isdigit(str[i]))
			return (0);
		++i;
	}
	return (1);
}


int word_count(char **array)
{
	int i;
	
	i = 0;
	while (*array)
	{
		++i;
		++array;
	}
	return(i);
}


int is_duplicates(int array_size char **array)
{
	int compare;
	int loop;
	char *temp;
	int i;

	loop = 0;

	while(loop < array_size)
	{
		
		while(1)
		{
			compare = ft_atoi(*temp);
			if (compare == ft_atoi(++temp))
				return (1);
		}
		loop++;
	}



return (1);

}



int main(int argc, char **argv)
{
	int i;
	char **temp;

	i = 0;
	argc--;
	argv = &argv[1];

	if (argc = 1)
	{
		argv = ft_strsplit(*argv, ' ');
		argc = word_count(argv);
	}

	while (i < argc)
	{
		if (!is_only_numbers_and_spaces(argv[i]))
			return (0);
		if (!custom_atoi(argv[i]))
			return (0);
		++i;
	}
	//if (is_duplicates(argv))
	//	return(0);

	return(1);
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



}