/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_clear.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeshin <jeshin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 15:33:46 by jeshin            #+#    #+#             */
/*   Updated: 2024/04/24 15:33:55 by jeshin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

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