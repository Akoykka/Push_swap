int is_sorted(t_list *head, int sort)
	{
		int curr_element_value;
		int next_element_value;
		static int i = 0;

		while (head->next)
		{
			curr_element_value = *((int *)head->content);
			next_element_value = *((int *)(head->next)->content);
			if (curr_element_value > next_element_value
				&& sort == ASCENDING)
				{
				printf("not sorted %d\n", i++);
				return (0);
				}
			if (curr_element_value < next_element_value
				&& sort == DESCENDING)
				{
				printf("not sorted %d\n", i++);
				return (0);
				}
			head = head->next;
		}
		return (1);
	}

	void bubble_sort_a(t_stack *stacks, t_list *head)
	{
		int	curr_element_value; ///valiaikainen
		int	next_element_value;
		int low;
		int high;


		high = get_nth_highest_number(head, 1);
		low  = get_nth_highest_number(head, stacks->size_a);

		while (!is_sorted(stacks->head_a, ASCENDING))
		{
			curr_element_value = *((int *)(stacks->head_a)->content);
			next_element_value = *((int *)(((stacks->head_a)->next)->content));


			printf("high is %i, Low is %i \n", high, low);
			printf("Curr %i  next %i\n", curr_element_value, next_element_value);

			if (curr_element_value < next_element_value
				|| (curr_element_value == high && next_element_value == low))
			{
				rotate(stacks, 'a');
				write(1, "equrotate\n", 10);
				ft_strcat(stacks->operations_a, "r");
			}
			else
			{
				swap(stacks, 'a');
				write(1, "swap\n", 5);
				ft_strcat(stacks->operations_a, "s");
			}
		}
	}

	void bubble_sort_b(t_stack *stacks, t_list *head)
	{
	int	curr_element_value; ///valiaikainen
	int	next_element_value;
	int low;
	int high;


	high = get_nth_highest_number(head, 1);
	low  = get_nth_highest_number(head, stacks->size_b);

	while (!is_sorted(stacks->head_b, DESCENDING))
	{
		curr_element_value = *((int *)(stacks->head_b)->content);
		next_element_value = *((int *)(((stacks->head_b)->next)->content));


		printf("high is %i, Low is %i \n", high, low);
		printf("Curr %i  next %i\n", curr_element_value, next_element_value);

		if (curr_element_value > next_element_value
			|| (curr_element_value == low && next_element_value == high))
		{
			rotate(stacks, 'b');
			write(1, "equrotate\n", 10);
			ft_strcat(stacks->operations_b, "r");
		}
		else
		{
			swap(stacks, 'b');
			write(1, "swap\n", 5);
			ft_strcat(stacks->operations_b, "s");
		}
	}
}



	void split_list(t_stack *stacks)
	{
		int pivot;
		int loop;
		int contents;
		t_list *temp;


		pivot = get_nth_highest_number(stacks->head_a, stacks->size_a / 2);
		printf("pivot value is:%i\n", pivot);
		int tempnumber = stacks->size_a / 2; /// en jaksanu keksia keksi sina tulevaisuuden-atte
		loop = stacks->size_a;
		while(loop--) //&& stacks->size_b == tempnumber)
		{
			contents = *((int *)(stacks->head_a)->content);
			if (contents < pivot)
				push_to(stacks, 'b');
			else
				rotate(stacks, 'a');
		}
		printf("b_stack size after split is %i\n", stacks->size_b);
	}
	void replace_swap_rotate_w_reverse_swap(char *start, int stack_size, int sr_count)
	{
		int loop;
		int the_rest;

		loop = stack_size - sr_count;
		the_rest = sr_count - loop;
		while (loop--)
		{
			*start = 'e';
			++start;
			*start = 's';
			++start;
		}
		while (the_rest--)
		{
			*start = ' ';
			++start;
		}
	}

	void optimize_rotateswap(char *operations, int stack_size)
{
	char *start;
	int sr_count;

	start = operations;
	while (*operations)
	{
		start = operations;
		sr_count = 0;
		while (*operations == 's' && *(operations + 1) == 'r')
		{
			operations += 2; 			//segfault chance !
			++sr_count;
		}
		if (sr_count > stack_size / 2)
			replace_swap_rotate_w_reverse_swap(start, stack_size, sr_count);

		++operations;
	}
}
	void replace_rotate_w_reverse(char *start, int stack_size, int r_count)
	{
		int loop;
		int the_rest;

		loop = stack_size - r_count;
		the_rest = r_count - loop;
		while (loop--)
		{
			*start = 'e';
			++start;
		}
		while (the_rest--)
		{
			*start = ' ';
			++start;
		}
	}

	void optimize_rotate(char *operations, int stack_size)
	{
		char *start;
		int r_count;

		int debug;
		debug = 0;
		start = operations;
		while (*operations)
		{
			start = operations;
			r_count = 0;
			while (*operations == 'r')
			{
				//printf("%d\n", debug++);
				++operations; 			//segfault chance !
				++r_count;

			}
			if (r_count > stack_size / 2)
				replace_rotate_w_reverse(start, stack_size, r_count);

			++operations;
		}
	}
	void replace_swap_rotate_w_push_rotate_push(char *start, int stack_size, int sr_count)
	{
		int loop;
		int the_rest;

		loop = sr_count - 2;

		*start = 'P';
		++start;
		*start = ' ';
		++start;

		while (loop--)
		{
			*start = 'R';
			++start;
			*start = ' ';
			++start;
		}

		*start = 'R';
		++start;
		*start = 'P';
		++start;

	}
	void optimize_push_rotate_push(char *operations, int stack_size)
	{
		char *start;  /////rotaten maara vaihtuu pushin aikana mahdollinen errorkohta
		int sr_count;

		start = operations;
		while (*operations)
		{
			start = operations;
			sr_count = 0;
			while (*operations == 's' && *(operations + 1) == 'r')
			{
				operations += 2;
				++sr_count;
			}
			if (sr_count > 2)
				replace_swap_rotate_w_push_rotate_push(start, stack_size, sr_count);

			++operations;
		}
	}
/*
void optimize_rotate(t_stack *stacks)
{
	while (*str)
	{
		if ()
			start counting how many
			if more than size / 2
				turn them into uppercase R



	}
}

Hypothesis 1: Optimizing bubblesort with pickup method over
merging merge-able operations afterwards.

Example one
Stack a:	srsrsrsrsrsr 			6 pairs of swaps 12 moves each
Stack b:	srsrsrsrsrsr

merge moves = SRSRSRSRSRSR			move both on the same time 12 moves total

if total size of stack is 6
total moves 2
one reverse rotate and swap is enough

if total size of stack is 12
total moves still 12



Example 2

push to stack and reverse one
Stack a:	srsrsrsrsrsr 			6 pairs of swaps 12 moves each
Stack b:	srsrsrsrsrsr

turn rs in to push and rotate


prrrrrrp 							push and rotate 6 times and push

prrrrrrp 							push and rotate 6 times and push

16 moves

cannot be merged because the other array works as a temporal storage;

if stacksize is 6

prp									push and reverse rotate and push

prp									push and reverse rotate and push


if stacksize is 12

16 moves

Merge wins, hypothesis is False.


Conclusion: Find way to merge optimally while leaving maximal optimization for pickup method

Also: Only rotations can be optimizaed to reduce amount of operations of a single stacks operations string.

Also: Find ways to optimize operations of a single string without taking away the ability to merge operations

kuinka monta rotatea tarvii etta array pyorahtaa ympari

parillinen maara valueita
rrrsrr 		isompi kuin jaettuna kahdella
6 / 2 = 3

rotaation maara takaperin =
6 - 3 = 3
6 - 5 = 1

pariton maara

5 / 2 = 2

rrsrr

rotaation maara takaperin =
5 - 2 = 3
5 - 3 = 2

Update:

systeemi toimii mutta viela on kymmenkertainen maara liikkeita

tuli idea sellaisesta algosta joka laskee optimaalisen reitin tai olemassa olevat luvut jotka on jarjestyksessa. ja stack b kerataan lukuja joita asetetaan takaisin stack a.

Nukutun yon jalkeen, luodaan int array joka sisaltaa jo oikealla paikalla olevat numerot jotka toimivat referenssina ja joka kerta kun numero pushataan oikealle paikalle se lisataan
myos listaan 

revelaatio 2: push on kaksi komentoa yhdessa: add to list and rotate

revelaatio 3: unessa etiaisen joka kerto etta kannattaa jakaa b-stack kahteen osioon toinen johon kerataan pienia numeroita ja toiseen puoleen isot numeroita



*/
int count_operations(char *str)
{
	int answer;

	answer = 0;
	while (*str)
	{
		if (ft_isalpha(*str))
			++answer;
		++str;
	}
	return(answer);
}

/*
int *get_best_ascending_order(t_list *head, t_sort *numbers, int index)
{
	int *list_of_numbers;
	t_list *temp;

	if (!temp && (index + 1) > numbers->size)
		ft_memcpy(numbers->best_asc_order, list_of_numbers, (index + 1)

	if (temp->content > list of number )
		add it to list
		get_best_ascending_order(move to next)
		delete it no need
		
	if (temp->content > list of number)
		dont add it to list
		get_best_ascending_order(move to next)
		delete it no need

	else 
		get_best_ascending_order(move to next)

}








//10 20 30 40 50 60 | [ 5  4 ] 3 2 1		tai		1 2 3 4 5 | [ 60  50 ] 40 30 20 10

t_sort *get_number_picking_order(t_list *head, t_sort *numbers)
{
	
	pushed numbers get added to already sorted


	malloc t_sort_struct

	get_best_ascending_order


	get_best_descending_order



	free malloc t_sort_struct
}

*/



int main(int arg_count, char **arg_values)
{
	t_stack *stacks;

	arg_values += 1;
	arg_count -= 1;
	if (arg_count == 0)
		ft_error();
	stacks = make_struct(arg_count, arg_values);








	split_list(stacks);

	//////
	printf("list A post split:\n");
	print_list(stacks->head_a);
	printf("list B post split:\n");
	print_list(stacks->head_b);
	// swap(stacks, 'a');
	// printf("Swap a:\n");
	// print_list(stacks->head_a);
	//rotate(stacks, 'a');
	//printf("Rotate a:\n");
	// print_list(stacks->head_a);
	// rotate(stacks, 'a');
	// printf("Rotate a:\n");
	print_list(stacks->head_a);
	/////

	bubble_sort_a(stacks, stacks->head_a);
	bubble_sort_b(stacks, stacks->head_b);

	///////
	print_list(stacks->head_a);
	printf("Operations a are :%s\n strlen is %zu\n",stacks->operations_a, ft_strlen(stacks->operations_a));
	print_list(stacks->head_b);
	printf("Operations b are :%s\n strlen is %zu\n",stacks->operations_b, ft_strlen(stacks->operations_b));
	printf("operationcount is %i\n", count_operations(stacks->operations_b));
	int r;
	int i;
	r = 0;
	i = 0;
	while ((stacks->operations_b)[i])
	{
		if ((stacks->operations_b)[i] == 'r')
			++r;
		++i;
	}
	printf("amount of r in operations_b %i\n", r);

	optimize_rotateswap(stacks->operations_b, stacks->size_b);

	r = 0;
	i = 0;
	while ((stacks->operations_b)[i])
	{
		if ((stacks->operations_b)[i] == 'r')
			++r;
		++i;
	}
	printf("Operations b are :%s\n strlen is %zu\n",stacks->operations_b, ft_strlen(stacks->operations_b));
	printf("amount of r in operations_b %i\n", r);
	printf("operationcount is %i\n", count_operations(stacks->operations_b));

	optimize_rotate(stacks->operations_b, stacks->size_b);

	printf("Operations b are :%s\n strlen is %zu\n",stacks->operations_b, ft_strlen(stacks->operations_b));
	printf("amount of r in operations_b %i\n", r);
	printf("operationcount is %i\n", count_operations(stacks->operations_b));

	optimize_push_rotate_push(stacks->operations_b, stacks->size_b);

	printf("Operations b are :%s\n strlen is %zu\n",stacks->operations_b, ft_strlen(stacks->operations_b));
	printf("amount of r in operations_b %i\n", r);
	printf("operationcount is %i\n", count_operations(stacks->operations_b));

	//simplify_operations(stacks)
	//optimize_swap(stacks);

	//optimize_rotate(stacks);
	//printf("Operations b are :%s\n strlen is %zu\n",stacks->operations_b, ft_strlen(stacks->operations_b));


	///////

	return (0);
}
