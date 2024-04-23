/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeshin <jeshin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 16:58:54 by jeshin            #+#    #+#             */
/*   Updated: 2024/04/22 17:23:55 by jeshin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex_bonus.h"

void	lstclear(t_lst **lst, void (*del)(void *))
{
	t_lst	*prv;

	if (!lst || !del)
		return ;
	while (*lst)
	{
		del((*lst)->content);
		prv = *lst;
		*lst = (*lst)->next;
		free(prv);
		prv = 0;
	}
}

int	lstsize(t_lst *lst)
{
	int	size;

	size = 0;
	while (lst)
	{
		lst = lst -> next;
		size++;
	}
	return (size);
}

t_lst	*lstnew(void *content)
{
	t_lst	*new;

	new = (t_lst *)malloc(sizeof(t_lst));
	if (!new)
		return (0);
	new->content = content;
	new->next = 0;
	return (new);
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