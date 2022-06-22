/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mnode_insert.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akoykka <akoykka@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 10:42:01 by akoykka           #+#    #+#             */
/*   Updated: 2022/06/22 10:46:00 by akoykka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

void ft_mnode_insert(t_mnode *dst, t_mnode *new_mnode)
{
	size_t 	i;
	t_mnode **new_next_index;

	i = 0;
	new_next_index = (t_mnode **)ft_memalloc(sizeof(t_mnode *) * (dst->next_size + 1));

	while (i < (dst->next_size))
	{
		new_next_index[i] = (dst->next)[i];
		++i;
	}
	(new_next_index)[i] = new_mnode;
	++(dst->next_size);
	//free old dst->next
	dst->next = new_next_index;
}