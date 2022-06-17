
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "libft/includes/libft.h"
# define ASCENDING 1
# define DESCENDING 0

typedef struct s_sort
{
	int current[500];
	int best_combination[500];
	int best_so_far;
}			t_sort;

void ft_lst_reverse(t_list **head)
{
	t_list *temp_prevnode = NULL;
	t_list *temp;
	t_list *temp_nextnode = NULL;

	if (!head || !*head)
		return;
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
	
	funktio

	if (!head)
	{
		save
	}
	while next number is higher
		save it 
		head = head->next
	
	functioncall with same index and head->next

	//here are all the resolves when smaller number;
	//in nondestructive manner must be resolved;
	//make linked list copy of current and solve it.




void  get_numbers_in_order(t_list *head, t_sort *numbers, int index, int order)
{
	static unsigned long long i = 0;

	while (head)
	{
		if (index == 0
			|| (order == ASCENDING
			&& *((int *)(head->content)) > (numbers->current)[index - 1]))
		{
			(numbers->current)[index] = *(int *)(head->content);
		}
		else
			get_numbers_in_order(head, numbers, index, order);

		head = head->next;
	}
	if (index > numbers->best_so_far)
	{
		ft_memcpy(numbers->best_combination, numbers->current, (index * 4));
		numbers->best_so_far = index;
		printf("found answer %lli amount of numbers is %i\n", i++ , numbers->best_so_far);
	}
}







/*
void  get_numbers_in_order(t_list *head, t_sort *numbers, int index, int order)
{
	static unsigned long long i = 0;

	++i;
	if (!head) // ||  )
	{
		if (index > numbers->best_so_far)
		{
			ft_memcpy(numbers->best_combination, numbers->current, (index * 4));
			numbers->best_so_far = index;
			printf("found answer %lli amount of numbers is %i\n", i, numbers->best_so_far);
		}
		return;
	}
	while (head)
	{
		if (index == 0
			|| (order == ASCENDING
			&& *((int *)(head->content)) > (numbers->current)[index - 1]))
			//|| ( order == DESCENDING
			//&& *((int *)(head->content)) < (numbers->current)[index - 1]))
		{
			(numbers->current)[index] = *(int *)(head->content);
			//get_numbers_in_order(head->next, numbers, (index + 1), order);
		}
		if ((numbers->current)[index] < *((int *)(head->content)))
		{
			(numbers->current)[index - 1] = *(int *)(head->content);
			get_numbers_in_order(head->next, numbers, index , order);
		}
		head = head->next;
	}
}
*/
//if (index == 0 || *((int *)(head->content)) > (numbers->current)[index]) 
	//	get_best_ascending_order(head->next, numbers, index);
	
void get_number_picking_order(t_list *head)
{
	t_sort *numbers;
	int i = 0;

	numbers = (t_sort *)malloc(sizeof(t_sort));
	numbers->best_so_far = 0;
	get_numbers_in_order(head, numbers, 0, ASCENDING);
	
	while (i < numbers->best_so_far)
	{
		printf("order is %i\n", numbers->best_combination[i++]);
	}
	

	




	//pushed numbers get added to already sorted

	//get_best_descending_order



	//free malloc t_sort_struct
}

t_list *make_list(char **array, int size)
	{
		t_list *head = NULL;
		t_list *new;
		int number;
		int i;

		i = 0;

		while(i < size)
		{
			number = ft_atoi(array[i]);
			new = ft_lst_new(&number, 4);
			ft_lst_add(&head, new);
			++i;
		}
		ft_lst_reverse(&head);
		return (head);
	}

int main (void)
{

	t_list *head;
	t_sort *ptr;
	char *string = "9162 7929 1548 9290 8252 39 4048 4307 8359 5736 6924 6748 420 992 7484 6500 553 4736 5321 5974 1245 8072 8650 4650 226 9158 8550 85 4855 8460 480 3146 4874 9155 4167 8993 5342 928 1773 182 3539 6594 8204 2751 2823 791 2234 6296 9058 1337 2920 35 6448 4583 4005 1348 6984 1475 2432 606 2897 9278 1174 7662 733 6527 998 6569 2100 8386 2411 757 4681 6551 8626 4372 2718 6143 8592 2310 2860 4769 6400 2662 2268 3522 8054 1109 7706 2394 1043 3068 1477 8679 8090 3736 1587 4069 1613 75 7110 5327 6563 6973 5148 1758 9317 1985 1848 9886 7087 1345 7553 1863 5392 6162 6358 8847 2453 2312 7018 7931 7372 5888 1535 2670 3853 4484 7968 9024 4018 9118 3678 8195 1427 4464 7187 5198 643 3552 9021 9218 3911 6392 9427 325 1983 1838 336 5231 2291 1918 3039 1712 458 9553 7216 2855 4384 9899 5775 6648 2456 3479 1907 4820 9680 1366 677 8256 344 5167 526 4919 6573 4695 655 6823 1720 3388 230 4490 6071 2714 1152 1996 4669 9002 6518 6107 4782 1160 6156 3874 3823 1532 401 4119 1335 8095 7627 8419 1342 2271 2703 520 8124 6076 3835 7458 7046 4371 6234 8317 5361 3440 3390 1039 3512 1234 2445 9931 15 4645 9442 2692 444 9980 4187 8418 7371 6181 7759 3710 8724 3405 853 2834 5300 2123 666 8941 7984 8785 5280 3553 6463 2090 4734 9962 8131 4576 652 8127 9134 1305 3748 2198 589 4527 4297 7516 9843 3375 6022 9711 1364 8745 3754 3980 8020 671 9329 8856 8880 3533 3735 9274 9147 8371 636 1517 3 200 6751 4362 2563 7092 7875 316 2896 3199 5298 2026 5128 4165 4816 695 9852 5498 3803 9100 7569 1836 6847 7761 2825 7840 883 3112 2368 7739 9028 176 5817 8729 8014 2911 2531 6652 634 3679 6992 5066 7063 9087 8004 180 5618 8561 6949 1422 5945 9611 5103 4330 707 4391 9936 971 2807 899 6328 5061 8600 4200 1760 4222 1227 4291 4452 3052 8035 3139 3511 1813 8410 4596 3740 9179 3507 6530 299 8406 2731 3478 3884 696 9725 2320 9507 1762 5982 8683 8176 6988 3992 4843 3845 1934 4896 2097 8832 4432 1598 1575 1073 6208 3791 2754 5002 2728 5422 1102 2036 6955 2770 8710 2477 7830 9166 5230 6350 4818 9375 7743 752 1044 847 4684 1087 611 3810 8913 73 3251 5083 6292 7425 2062 8324 4273 6012 3943 6381 3293 3554 5856 4638 2471 6947 4446 8446 147 3863 1333 5064 5045 7640 6291 8277 7282 4417 4956 6735 4927 9842 3724 4252 5729 1808 4848 9733 3452 3324 2711 8594 2856 5376 8318 3283 7593 5939 758 1300 1138 6050 5133 6892 9327 860 1651 8036 8882 1476 2697 5611 3597 9264 1866 4082 6161 1525 4637 922 41 4083 3549 1691 4012 6347 6081 7215 6017 2644 5644 8328 3190 7648 5821";

	head = make_list(ft_strsplit(string, ' '), 500);
	get_number_picking_order(head);

	/*
							/// condition when end has been reached
							/// go x times which is lenght of string
							// or when you find sorted portion
							// check for sorted numbers

	while(is_sorted(stack_a))
	{
		while(go forward)
				
		ft_dump_high_numbers(numbers);
		ft_dump_low_numbers(numbers);
	}
							// go backwards until you hit first moved number
							/// or until in the last position of chained list is moved number
	*/
	



	return (0);
}