
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

int is_smaller_than_max(char *str)
{
	if (ft_isdigit(*str) && ft_strcmp(str, "2147483647") < 0)
		return (0);
	return (1);
}

int is_bigger_than_min(char *str)
{

	if (*str == '-' && ft_strcmp(str, "-2147483648") < 0)
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
		if (ft_strcmp(target, numbers[index]) == 0)
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
			|| !is_dup(input, i, size))
			return(0);
		++i;
	}
	return(1);
}

int	*make_int_array (char **array, int size)
{
	int	*stack;
	int	i;

	i = 0;
	stack = (int *)ft_memalloc(sizeof(int) * (size));
	if (!stack)
		return (NULL);
	while (size > i)
	{
		stack[i] = ft_atoi(array[i]);
		++i;
	}
	return (stack);
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
	if(!new)
		return;
	new->next = *list;
	*list = new;
}

void llist_destroy(t_llist **list)
{
	t_llist *temp;
	t_llist *next;

	if(!list)
		return ;
	next = NULL;
	temp = *list;

	while(temp)
	{
		next = temp->next;
		free(temp);
		temp = next;
	}
	list = NULL;
}

t_llist *make_list (char **array, int size)
{	
	int i;
	int *array;
	t_llist *head;
	t_llist *new;

	i = 0;
	head = NULL;
	new = NULL;
	array = NULL;

	array = make_int_array(array, size);
	if (!array)
		return (NULL);
	while (size > i)
	{
		new = llist_new(array[i])
		if (!new)
		{
			llist_destroy(&head);
			return (NULL);
		}
		llist_add(&head, new);
		++i;
	}
	llist_rev(&head);
	free(array);
	return (head);
}


int main (int arg_count, char **arg_values)
{
	char **numbers;
	t_llist *list;

	list = NULL;
	numbers = NULL;
	arg_count--;
	arg_values++;

	if(arg_count == 1)
	{
		numbers = ft_strsplit(*arg_values, ' ');
		if (!is_valid_input(numbers, count_numbers(numbers)))
			exit(1);
		list = make_list(numbers, count_numbers(numbers));
		free(numbers);
	}
	else
	{
		if (!is_valid_input(arg_values, size))
			exit(1);
		list = make_list(arg_values, arg_count);
	}
	if (!list)
		exit(1);



}
