/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seunghan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/15 11:39:04 by seunghan          #+#    #+#             */
/*   Updated: 2024/04/14 18:17:36 by seunghan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(t_list *now)
{
	static int	idx_s;
	t_list		*new;

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
