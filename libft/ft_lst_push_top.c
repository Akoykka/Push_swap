/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_push_top.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akoykka <akoykka@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 16:33:16 by akoykka           #+#    #+#             */
/*   Updated: 2022/06/07 20:44:30 by akoykka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

void ft_lst_push_top(t_list **src, t_list **dest)
{
	t_list	*temp;
	
	if (!src || !dest)
		return;
	temp = *src;
	*src = (*src)->next;
	temp->next = *dest;
	*dest = temp;
}
