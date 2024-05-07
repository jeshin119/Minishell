/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeshin <jeshin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 15:59:59 by seunghan          #+#    #+#             */
/*   Updated: 2024/04/24 15:35:07 by jeshin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

t_list	*ft_lstlast(t_list *lst)
{
	if (!(lst))
		return (0);
	while (lst -> next)
		lst = lst -> next;
	return (lst);
}

t_lst	*lstlast(t_lst *lst)
{
	if (!lst)
		return (0);
	while (lst-> next)
		lst = lst->next;
	return (lst);
}
