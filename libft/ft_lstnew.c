/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeshin <jeshin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/15 11:39:04 by seunghan          #+#    #+#             */
/*   Updated: 2024/05/01 11:29:31 by jeshin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(t_list *now)
{
	static int	idx_s;
	t_list		*new;

	if (!now)
		idx_s = 0;
	new = (t_list *)malloc(sizeof(t_list));
	if (!new)
		exit(1);
	new -> token_idx = idx_s;
	new -> d_quote = 0;
	new -> s_quote = 0;
	new -> alloc = 0;
	new -> ctrl_token = 0;
	new -> quote_to_space = 0;
	new -> next = 0;
	new -> prev = now;
	if (now)
		now -> next = new;
	idx_s++;
	return (new);
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