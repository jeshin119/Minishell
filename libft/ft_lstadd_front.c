/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeshin <jeshin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 17:28:05 by jeshin            #+#    #+#             */
/*   Updated: 2024/05/09 15:54:22 by jeshin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_front(t_list **lst, t_list *new)
{
	t_list	*tmp;

	if (!lst)
		return ;
	if (*lst)
	{
		tmp = new;
		while (tmp->next)
			tmp = tmp->next;
		tmp -> next = (*lst);
		(*lst) = new;
	}
	else
		*lst = new;
}

void	lstadd_front(t_lst **lst, t_lst *new)
{
	t_lst	*tmp;

	if (!lst)
		return ;
	if (*lst)
	{
		tmp = new;
		while (tmp->next)
			tmp = tmp->next;
		tmp -> next = (*lst);
		(*lst) = new;
	}
	else
		*lst = new;
}
