
The first, named checker which takes integer arguments
and reads instructions on the standard output.
Once read, checker executes them and displays OK
if integers are sorted. Otherwise, it will display KO

To start with:
a contains a random number of either positive or negative numbers without any duplicates.
b is empty



jotta voi ottaa mukaan myos tsydeemeja jossa useampi argumentti voidaan tarkistaa ensiksi
etta onko valeja inputissa. jos on voi strsplittaa (silloin on mallocoitu) tai voidaan
tarkista vain etta onko yksi argumentti ?;


Eli ensiksi, katso onko kasiteltava numero =

pelkkia numeroita;
strcmp isompi kuin min_int
strcmp pienempi kuin max_int
sama kuin joku numero sen jalkeen;

samaa funktiota voi kayttaa myos push_swapissa.

dispatch
	push_stack()
	swap()
	rotate()
	rrotate()

	ra rb rr, rra, rrb, rrr, sa, sb, ss, pa, pb.

int is_only_numbers(char *str)
{
	while (*str)
	{
		if (!ft_isdigit(*str))
			return(0);
		++str;
	}
	return(1);
}

int is_smaller_than_max(*str)
{
	if (ft_isdigit(*str) && ft_strcmp(str, "21398210938098213") > 0)
		return (0);
	return (1);
}

int is_bigger_than_min(*str)
{

	if (*str == '-' && ft_strcmp(str, "-123123123213213") < 0)
		return (0);
	return(1);
}

int is_dup(char **numbers, int index, int size)
{
	char *target;

	target = numbers[index];
	++index;
	while (size > index)
	{
		if (!ft_strcmp(target, numbers[index]))
			return(1);
		++index;
	}
	return (0);
}


int is_valid_input(char **input, int size)
{
	int i;

	i = 0;
	while(size > i)
	{	if (!is_only_numbers(input[i])
			|| !is_smaller_than_max(input[i])
			|| !is_bigger_than_min(input[i])
			|| is_dup(input, i, size))
			return(0);
		++i;
	}
	return(1);
}




void main (int arg_count, char **arg_values)
{
	char **numbers;

	numbers = NULL;
	arg_count--;
	arg_values++;

	if(arg_count == 1)
	{
		numbers = ft_strsplit(*arg_values, ' ');
		if (!is_valid_input(numbers, count_numbers(numbers)))
			exit(1);
		make_list(numbers, count_numbers(numbers));
		free(numbers)
	}
	else
	{
		if (!is_valid_input(arg_values, size))
			exit(1);
		make_list(arg_values);
	}


}
