/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seunghan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 16:13:56 by seunghan          #+#    #+#             */
/*   Updated: 2024/05/02 15:06:53 by seunghan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

static int	reduce_bs_len(char const *s, int start, int len)
{
	int	reduce_stack;
	int	start_const;

	reduce_stack = 0;
	start_const = start;
	if (!len)
		return (0);
	while (start <= start_const + len && s[start])
	{
		if (s[start] == '\\')
		{
			reduce_stack++;
			start++;
		}
		start++;
	}
	len -= reduce_stack;
	return (len);
}

static void	handle_bs(char const *s, int *start)
{
	if (s[(*start)] == '\\')
		(*start)++;
}

char	*ft_substr(char const *s, int start, int len)
{
	char	*sub_s;
	int		i;

	i = ft_strlen(s);
	if (len + start > i && start < i)
	{
		len = i;
		len = len - start;
	}
	else if (start >= i)
		len = 0;
	len = reduce_bs_len(s, start, len);
	sub_s = (char *)malloc(len * sizeof(char) + 1);
	if (!(sub_s))
		exit(1);
	i = 0;
	while (i < len && s[start])
	{
		handle_bs(s, &start);
		sub_s[i] = s[start];
		i++;
		start++;
	}
	sub_s[i] = 0;
	return (sub_s);
}
