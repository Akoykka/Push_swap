/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akoykka <akoykka@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 13:23:00 by akoykka           #+#    #+#             */
/*   Updated: 2022/08/12 13:05:45 by akoykka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"


///// OPERATIONS START
void 	push_stack(t_sort *sort, int stack)
{
	t_llist *target;

	if (stack == STACK_A)
	{
		target = sort->stack_a;
		sort->stack_a = sort->stack_a->next;
		target->next = sort->stack_b;
		sort->stack_b = target;
	}
	if (stack == STACK_B)
	{
		target = sort->stack_b;
		sort->stack_b = sort->stack_b->next;
		target->next = sort->stack_a;
		sort->stack_a = target;
	}
}

void rotate_stack_a(t_sort *sort, int direction)
{
	t_llist *temp;
	t_llist *target;

	temp = NULL;
	target = NULL;

	if (direction == FORWARD && llist_len(sort->stack_a) > 1)
	{
	target = sort->stack_a;
	sort->stack_a = sort->stack_a->next;
	get_llist_tail(sort->stack_a)->next = target;
	target->next = NULL;
	}

	if (direction == BACKWARD && llist_len(sort->stack_a) > 1)
	{
	target = get_llist_tail(sort->stack_a);
	temp = sort->stack_a;
	while(temp->next != target)
		temp = temp->next;
	temp->next = NULL;
	target->next = sort->stack_a;
	sort->stack_a = target;
	}
}

void rotate_stack_b(t_sort *sort, int direction)
{
	t_llist *temp;
	t_llist *target;

	temp = NULL;
	target = NULL;

	if (direction == FORWARD && llist_len(sort->stack_b) > 1)
	{
		target = sort->stack_b;
		sort->stack_b = sort->stack_b->next;
		(get_llist_tail(sort->stack_b))->next = target;
		target->next = NULL;
	}
	if (direction == BACKWARD && llist_len(sort->stack_b) > 1)
	{
		target = get_llist_tail(sort->stack_b);
		temp = sort->stack_b;
		while(temp->next != target)
			temp = temp->next;
		temp->next = NULL;
		target->next = sort->stack_b;
		sort->stack_b = target;
	}
}

void rotate_both_stacks(t_sort *sort, int direction)
{
	rotate_stack_a(sort, direction);
	rotate_stack_b(sort, direction);
}
///// OPERATIONS END

//// VALIDATOR START
int is_only_numbers(char *str)
{
	if (*str == '-' && ft_strlen(str) > 1)
		++str;
	while (*str)
	{
		if (!ft_isdigit(*str))
		{
			printf("isonlynumbers failed\n");
			return(0);
		}
		++str;
	}
	return(1);
}

int is_bigger_than_max(char *str)
{
	if (ft_isdigit(*str))
	{
		if (ft_strlen(str) > 10)
		{
			printf("bigger than max failed(number was %s)\n ", str);
			return (1);
		}
		if (ft_strlen(str) == 10
			&& ft_strcmp(str, "2147483647") > 0)
		{
			printf("bigger than max failed(number was %s)\n ", str);
			return (1);
		}
	}
	return (0);
}

int is_smaller_than_min(char *str)
{
	if(*str == '-')
	{
		if (ft_strlen(str) > 11)
		{
			printf("smaller than min failed\n");
			return (1);
		}
		if (ft_strlen(str) == 11
			&& ft_strcmp(str, "-2147483648") > 0)
		{
			printf("smaller than min failed\n");
			return (1);
		}
	}
	return(0);
}

int is_dup(char **numbers, int index, int size)
{
	char *target;

	target = numbers[index];
	++index;
	while (size > index)
	{
		if (ft_strcmp(target, numbers[index]) == 0)
		{
			printf("isdup failed\n");
			return(1);
		}
		++index;
	}
	return (0);
}


int is_valid_input(char **input, int size)
{
	int i;

	i = 0;
	if(!input || !size)
		return(0);
	while(size > i)
	{	if (!is_only_numbers(input[i])
			|| is_bigger_than_max(input[i])
			|| is_smaller_than_min(input[i])
			|| is_dup(input, i, size))
			return(0);
		++i;
	}
	return(1);
}
//// VALID END
///////

t_llist	*char_array_to_llist(char **array, int size)
{
	t_llist	*head;
	t_llist	*new;
	int		i;

	head = NULL;
	i = 0;
	if (!is_valid_input(array, size))
	{
		printf("ERROR NOT VALID NUMBERS");
		return (NULL);
	}
	while (size > i)
	{
		new = llist_new(ft_atoi(array[i]));
		if (!new)
		{
			llist_destroy(&head);
			return (NULL);
		}
		llist_add(&head, new);
		++i;
	}
	llist_rev(&head);
	return(head);
}

/// ASSIGN CHUNKS

t_llist *find_smallest(t_llist *list)
{
	t_llist* smallest;

	smallest = list;
	while(list)
	{
		if (list->content < smallest->content)
			smallest = list;
		list = list->next;
	}
	return(smallest);
}

t_llist *find_next_smallest(t_llist *list, int prev_value)
{
	t_llist *temp;
	int new_low;
	while (list->content <= prev_value)
		list = list->next;

	temp = list;
	new_low = list->content;

	while(list)
	{
		if (list->content < new_low
			&& list->content > prev_value)
		{
			temp = list;
			new_low = list->content;
		}
		list = list->next;
	}
	return (temp);
}


int assign(t_sort *sort, int n)
{
	float total;
	int chunk;

	total = (float)llist_len(sort->stack_a);
	chunk = (float)n / total / sort->split;
	//printf("total %f / nth low %i / split %f = chunk %i\n", total, n, sort->split, chunk);
	if ((int)total == n && sort->split != 1.0f / 7.0f)
		return(chunk - 1);
	return(chunk);
}
void print_list_delete(t_llist *list)
{
	int nodecount;

	nodecount = 0;
	if (!list)
		printf("EMPTY LIST\n");
	while(list)
	{
		ft_putnbr(list->content);
		printf("\t\t (Chunk: %i)", list->chunk);
		printf("\n");
		list = list->next;
		nodecount++;
	}
	printf("list_len = %i\n", nodecount);
}
void assign_chunks(t_sort *sort)
{
	int n;
	int value;
	t_llist *current;
	///
	//sort->split = 1.0f / 7;
	////
	n = 1;
	current = find_smallest(sort->stack_a);
	value = current->content;
	current->chunk = assign(sort, n);
	//printf("assigned number is %i\n",current->content);

	while (n < llist_len(sort->stack_a))
	{
		++n;
		current = find_next_smallest(sort->stack_a, value);
		current->chunk = assign(sort, n);
		value = current->content;
		//printf("assigned number is %i\t chunk is %i \n",current->content,current->chunk);
	}
	////
	//print_list_delete(sort->stack_a);
	//exit(1);
	//////
}
//// ASSIGN END

void free_array(char **str)
{
	int i;

	i = 0;
	while(str[i])
	{
		free(str[i]);
		str[i] = NULL;
		++i;
	}
}

int getarrlen(char **str)
{
	int len;

	len = 0;
	while(str[len])
		++len;
	return (len);
}

void make_struct(t_sort *sort, int argc, char **argv)
{
	char	**temp;

	temp = NULL;
	if (argc == 1)
	{
		ft_strsplit(*argv, ' ');
		sort->stack_a = char_array_to_llist(temp, getarrlen(temp));
		free_array(temp);
		temp = NULL;
	}
	else
		sort->stack_a = char_array_to_llist(argv, argc);
	if (!sort->stack_a)
	{
		printf("malloc error(makestruct)\n");
		exit(1);
	}
	assign_chunks(sort);
	sort->stack_b = NULL;
	sort->moves = NULL;
}

float adjust_split(void)
{
	static int	counter = 1;

	++counter;
	return(1.0f / counter);
}

////
////Travel End`
////

///
//// COMPARE START
///
int get_bigger(int value, int valuetwo)
{
	if (value > valuetwo)
		return (value);
	return(valuetwo);
}
void compare_both_forward(t_optim *optm)
{
	int total_moves;

	total_moves = get_bigger(optm->forward_a, optm->forward_b);
	if	(total_moves < optm->least_moves)
	{
		optm->a_direction = FORWARD;
		optm->b_direction = FORWARD;
		optm->best_a = optm->forward_a;
		optm->best_b = optm->forward_b;
		optm->best_target = optm->value;
		optm->least_moves = total_moves;
	}

}
void compare_both_backward(t_optim *optm)
{
	int total_moves;

	total_moves = get_bigger(optm->backward_a, optm->backward_b);
	if	(total_moves < optm->least_moves)
	{
		optm->a_direction = BACKWARD;
		optm->b_direction = BACKWARD;
		optm->best_a = optm->backward_a;
		optm->best_b = optm->backward_b;
		optm->best_target = optm->value;
		optm->least_moves = total_moves;
	}
}
void compare_forward_a_backward_b(t_optim *optm)
{
	int total_moves;

	total_moves = optm->forward_a + optm->backward_b;
	if	(total_moves < optm->least_moves)
	{
		optm->a_direction = FORWARD;
		optm->best_a = optm->forward_a;
		optm->b_direction = BACKWARD;
		optm->best_b = optm->backward_b;
		optm->best_target = optm->value;
		optm->least_moves = total_moves;
	}
}
void compare_forward_b_backward_a(t_optim *optm)
{
	int total_moves;

	total_moves = optm->forward_b + optm->backward_a;
	if	(total_moves < optm->least_moves)
	{
		optm->b_direction = FORWARD;
		optm->best_b = optm->forward_b;
		optm->a_direction = BACKWARD;
		optm->best_a = optm->backward_a;
		optm->best_target = optm->value;
		optm->least_moves =  total_moves;
	}
}

void compare_results(t_optim *optm)
{
	compare_both_forward(optm);
	compare_both_backward(optm);
	compare_forward_a_backward_b(optm);
	compare_forward_b_backward_a(optm);
}
///
//// COMPARE END


int get_travel_a(t_sort *sort, t_llist *target)
{
	int travel;
	t_llist *temp;

	travel = 0;
	temp = sort->stack_a;
	while(temp != target)
	{
		++travel;
		temp = temp->next;
	}
	return (travel);
}

//// TRAVEL CALC
///START

int is_biggest(t_sort *sort, int value)
{
	t_llist *temp;

	temp = sort->stack_b;
	while (temp)
	{
		if (temp->content > value)
			return(0);
		temp = temp->next;
	}
	return (1);
}
int is_smallest(t_sort *sort, int value)
{
	t_llist *temp;

	temp = sort->stack_b;
	while (temp)
	{
		if (temp->content < value)
			return(0);
		temp = temp->next;
	}
	return (1);
}


int get_travel_b(t_sort *sort, int value)
{
	int travel;
	t_llist *temp;

	travel = 0;
	temp = sort->stack_b;
	while(temp)
	{
		if (is_biggest(sort, temp->content)
			 && (temp->content < value || is_smallest(sort, value)))
			return (travel);

		if (temp->next && value < temp->content && value > temp->next->content)
			return (travel + 1);

		temp = temp->next;
		++travel;
	}
	return (0);
}
///
//// TRAVEL CALC END
///

int convert(int travel, int size)
{
	if (travel)
		return (size - travel);
	return (travel);
}


void get_next_target(t_sort *sort, int current_chunk)
{
	t_optim optm;
	t_llist *temp;

	temp = sort->stack_a;
	ft_memset(&optm, 0, sizeof(t_optim));
	optm.least_moves = 999999;
	while (temp)
	{
		if (temp->chunk == current_chunk)
		{
			//if(llist_len(sort->stack_a) == 2)
			//	printf("wtf push plx\n");
			optm.forward_a = get_travel_a(sort, temp);
			optm.forward_b = get_travel_b(sort, temp->content);
			optm.backward_a = convert(optm.forward_a, llist_len(sort->stack_a));
			optm.backward_b = convert(optm.forward_b, llist_len(sort->stack_b));
			optm.value = temp->content;
			compare_results(&optm);
		}
		temp = temp->next;
	}
	sort->curr_target = optm.best_target;
	sort->a_direction = optm.a_direction;
	sort->a_rotation = optm.best_a;
	sort->b_direction = optm.b_direction;
	sort->b_rotation = optm.best_b;
}
//// LLIST FUNCTIONS
int is_curr_chunk_sorted(t_sort *sort, int curr_chunk)
{
	t_llist *temp;

	temp = sort->stack_a;
	while(temp)
	{
		if (temp->chunk == curr_chunk)
			return (0);
		temp = temp->next;
	}
	return (1);
}

t_llist *get_llist_tail(t_llist *list)
{
	t_llist *temp;

	temp = list;
	if(!temp)
	{
		printf("error no list (get_tail");
		return (NULL);
	}
	while (temp->next)
		temp = temp->next;
	return (temp);
}

void llist_add_tail(t_llist *head, t_llist *new)
{
	if(!head)
	{
		head = new;
		return ;
	}
	(get_llist_tail(head))->next = new;
	new->next = NULL;
}

void add_move(t_sort *sort, int move_id, int direction)
{
	t_llist *new;

	new = llist_new(move_id);
	if (!new)
	{
			llist_destroy(&sort->stack_a);
			sort->stack_a = NULL;
			llist_destroy(&sort->stack_b);
			sort->stack_b = NULL;
			llist_destroy(&sort->moves);
			sort->moves = NULL;
			llist_destroy(&sort->current_best);
			sort->current_best = NULL;
			printf("malloc failed on move_write");
			exit(1);
	}
	if (direction == BACKWARD)
		new->content += 1;
	llist_add(&sort->moves, new);
}

void move_target_to_stack_b(t_sort *sort)
{
	//if(sort->curr_target == 532 || sort->curr_target == 488)
	//{
	//printf("target is: %i\n", sort->curr_target);
	//printf("most optimal move is b_direction: %i b_rotation: %i\n", sort->b_direction, sort->b_rotation);
	//printf("most optimal move is a_direction: %i a_rotation: %i\n", sort->a_direction, sort->a_rotation);
//	}
	while (sort->a_rotation || sort->b_rotation)
	{
		if (sort->a_direction == sort->b_direction
			&& sort->a_rotation && sort->b_rotation)
		{
			rotate_both_stacks(sort, sort->a_direction);
			add_move(sort, ROTATE_BOTH, sort->a_direction);
			sort->a_rotation--;
			sort->b_rotation--;
		}
		else if (sort->a_rotation)
		{
			rotate_stack_a(sort, sort->a_direction);
			add_move(sort, ROTATE_A, sort->a_direction);
			sort->a_rotation--;
		}
		else
		{
			rotate_stack_b(sort, sort->b_direction);
			add_move(sort, ROTATE_B, sort->b_direction);
			sort->b_rotation--;
		}
	}
	//if(sort->stack_a->content == 532 || sort->stack_a->content == 488)
	//{
	///printf("target is: %i\n", sort->curr_target);
	//printf("most optimal move is b_direction: %i b_rotation: %i\n", sort->b_direction, sort->b_rotation);
	//printf("most optimal move is a_direction: %i a_rotation: %i\n", sort->a_direction, sort->a_rotation);
	//print_list_delete(sort->stack_a);
	//print_list_delete(sort->stack_b);
	//}
	push_stack(sort, STACK_A);
	add_move(sort, PUSH_A, FORWARD);
}


/////
//// ALIGN BIGGEST NUMBER START
int get_big(t_llist *list)
{
	int big;

	big = list->content;
	while(list)
	{
		if (big < list->content)
			big = list->content;
		list = list->next;
	}
	return (big);
}

int get_dist_to_big(t_llist *list, int big)
{
	int distance;

	distance = 0;

	while (list && list->content != big)
	{
		distance++;
		list = list->next;
	}
	return (distance);
}


void align_biggest_number(t_sort *sort)
{
	int distance;
	int direction;

	direction = FORWARD;
	distance = get_dist_to_big(sort->stack_b, get_big(sort->stack_b));
	if (distance > (llist_len(sort->stack_b) / 2))
	{
		distance = llist_len(sort->stack_b) - distance;
		direction = BACKWARD;
	}
	while(distance)
	{
		rotate_stack_b(sort, direction);
		add_move(sort, ROTATE_B, direction);
		--distance;
	}
}

/////
///// ALIGN BIGGEST NUMBER END
////


void sort_integers(t_sort *sort)
{
	int total_chunks;

	total_chunks = 1.0f / sort->split;
	while(total_chunks)
	{
		while(!is_curr_chunk_sorted(sort, total_chunks - 1))
		{
			get_next_target(sort, total_chunks - 1);
			move_target_to_stack_b(sort);
		}
		--total_chunks;
	}
	align_biggest_number(sort);
	while(sort->stack_b)
	{
		push_stack(sort, STACK_B);
		add_move(sort, PUSH_B, FORWARD);
	}

}

int is_it_sorted(t_sort *sort)
{
	t_llist *temp;

	temp = sort->stack_a;
	if (sort->stack_b != NULL)
		return (0);
	while(temp && temp->next)
	{
		if(temp->content > temp->next->content)
			return(0);
		temp = temp->next;
	}
	return(1);
}

void is_sorted(t_sort *sort)
{
	t_llist *temp;

	temp = sort->stack_a;
	if (sort->stack_b != NULL)
		printf("stack_b is not empty at split %f\n", sort->split);
	while(temp && temp->next)
	{
		if(temp->content > temp->next->content)
		{
			printf("not valid input at split %f\n stack_a is:\n", sort->split);
			print_list_delete(sort->stack_a);
			break ;
		}
		temp = temp->next;
	}
}

void compare_sort(t_sort *sort)
{
	if ( is_it_sorted(sort) && (sort->current_best == NULL
	 		|| llist_len(sort->moves) < llist_len(sort->current_best)))
		{
			llist_destroy(&sort->current_best);
			sort->current_best = sort->moves;
			sort->moves = NULL;
		}
}

void reset_struct(t_sort *sort)
{
	llist_destroy(&sort->stack_a);
	sort->stack_a = NULL;
	llist_destroy(&sort->stack_b);
	sort->stack_b = NULL;
	llist_destroy(&sort->moves);
	sort->moves = NULL;
}

//
//// DEBUG
//

void print_list(t_llist *list)
{
	int nodecount;

	nodecount = 0;
	if (!list)
		printf("EMPTY LIST\n");
	while(list)
	{
		ft_putnbr(list->content);
		if (list->content == PUSH_A)
			printf("\t PUSH_A");
		if (list->content == PUSH_B)
			printf("\t PUSH_B");
		if (list->content == ROTATE_A)
			printf("\t ROTATE_A");
		if (list->content == RROTATE_A)
			printf("\t RROTATE_A");
		if (list->content == ROTATE_B)
			printf("\t ROTATE_B");
		if (list->content == RROTATE_B)
			printf("\t RROTATE_B");
		if (list->content == ROTATE_BOTH)
			printf("\t RROTATE_B");
		if (list->content == RROTATE_BOTH)
			printf("\t RROTATE_B");
		printf("\t\t (Chunk: %i)", list->chunk);
		printf("\n");
		list = list->next;
		nodecount++;
	}
	printf("list_len = %i\n", nodecount);
}

//
///DEBUG END
//

void print_moves(t_llist *list)
{
	while(list)
	{
		if (list->content == PUSH_A)
			printf("pa\n");
		if (list->content == PUSH_B)
			printf("pb\n");
		if (list->content == ROTATE_A)
			printf("ra\n");
		if (list->content == RROTATE_A)
			printf("rra\n");
		if (list->content == ROTATE_B)
			printf("rb\n");
		if (list->content == RROTATE_B)
			printf("rrb\n");
		if (list->content == ROTATE_BOTH)
			printf("rr\n");
		if (list->content == RROTATE_BOTH)
			printf("rrr\n");
		list = list->next;
	}
}

int main(int arg_count, char **arg_values)
{
	t_sort sort;

	arg_count -= 1;
	arg_values += 1;

	sort.current_best = NULL;
	sort.split = 1.0f / 1.0f ;
	while ((1.0f / 12.0f) < sort.split)
	{
		make_struct(&sort, arg_count, arg_values);
		sort_integers(&sort);
		/// DEBUG
		//is_sorted(&sort);
		/// DEBUG
		compare_sort(&sort);
		sort.split = adjust_split();
		reset_struct(&sort);
	}
	llist_rev(&sort.current_best);
	//print_list(sort.current_best);
	print_moves(sort.current_best);
	llist_destroy(&sort.current_best);
	return (0);
}
//$>ARG="4 67 3 87 23"; ./push_swap $ARG | wc -l
//$>ARG="388 230 1234 380 331 961 1011 1193 332 363 1086 839 206 652 519 581 747 894 1077 34 1203 1270 876 1132 1268 1230 420 1127 209 768 248 14 1128 1070 1117 44 1250 211 61 1007 122 1098 690 597 374 29 647 703 587 329 931 777 692 196 521 968 1290 572 948 439 1194 607 237 1105 766 721 530 969 739 527 1019 1185 407 701 252 883 631 1002 665 1174 352 403 1287 30 41 99 1226 17 809 770 1243 991 453 385 676 731 444 477 980 411 1277 171 778 1221 528 157 543 712 1024 993 536 1085 154 339 760 934 1093 992 309 557 910 585 190 466 148 265 819 315 262 442 677 1125 470 952 843 109 722 734 437 942 269 998 855 825 383 191 1099 472 205 849 412 103 21 933 251 1224 774 794 1172 1012 1082 1013 243 354 155 529 795 545 971 451 1183 906 419 850 752 233 36 91 165 965 239 1190 1102 1255 1126 808 911 944 1147 1136 872 807 596 905 340 1100 939 59 1181 40 1291 389 173 1046 814 152 1005 866 433 875 1120 1175 561 1153 454 292 610 588 293 181 37 490 1049 798 621 1297 1079 518 954 1143 1206 461 579 614"; ./push_swap $ARG | ./checker $ARG
//OK