/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akoykka <akoykka@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/29 10:51:25 by akoykka           #+#    #+#             */
/*   Updated: 2022/08/13 17:05:19 by akoykka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

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
