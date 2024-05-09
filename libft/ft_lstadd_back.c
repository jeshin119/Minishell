/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeshin <jeshin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 18:03:36 by jeshin            #+#    #+#             */
/*   Updated: 2024/05/09 15:54:17 by jeshin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*pos;

	if (!lst)
		return ;
	pos = *lst;
	if (pos)
	{
		while (pos->next)
			pos = pos->next;
		pos->next = new;
	}
	else
		*lst = new;
}

void	lstadd_back(t_lst **lst, t_lst *new)
{
	t_lst	*pos;

	if (!lst)
		return ;
	pos = *lst;
	if (pos)
	{
		while (pos->next)
			pos = pos->next;
		pos->next = new;
	}
	else
		*lst = new;
}
