/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akoykka <akoykka@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 12:18:08 by akoykka           #+#    #+#             */
/*   Updated: 2022/06/22 14:43:32 by akoykka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H
# include <stdlib.h>
# include <stdio.h>
# include "libft/includes/libft.h"
# define ASCENDING 1
# define DESCENDING 0

typedef struct s_solve
{
	int			numbers[500];
	int			solved[500];
	int			asc[500];
	int			desc[500];

	int			current[500];
	
	int 		answer[500];
	size_t		answer_depth;
}			t_solve;

typedef struct s_insert
{
	int			value;
	
	size_t		max_depth;
	t_mnode 	*insert_point;
}			t_insert;

#endif