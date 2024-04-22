/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seunghan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 13:56:25 by seunghan          #+#    #+#             */
/*   Updated: 2024/04/09 12:59:07 by seunghan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

static size_t	frontchk(char const *s1, char const *set)
{
	size_t	i;
	size_t	j;
	size_t	len;

	i = 0;
	len = 0;
	while (s1[i])
	{
		j = 0;
		while (set[j])
		{
			if (s1[i] == set[j])
			{
				len++;
				break ;
			}
			j++;
		}
		if (i + 1 != len)
			return (len);
		i++;
	}
	return (len);
}

static size_t	backchk(char const *s1, char const *set)
{
	size_t	s1_len;
	size_t	j;
	size_t	i;
	size_t	len;

	len = 0;
	s1_len = ft_strlen(s1) - 1;
	i = s1_len;
	while (s1_len >= 0)
	{
		j = 0;
		while (set[j])
		{
			if (s1[s1_len] == set[j])
			{
				len++;
				break ;
			}
			j++;
		}
		if (i - (s1_len - 1) != len)
			return (len);
		s1_len--;
	}
	return (len);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*ret;
	size_t	front_len;
	size_t	back_len;
	size_t	ret_len;

	front_len = frontchk(s1, set);
	back_len = backchk(s1, set);
	ret_len = ft_strlen(s1) - (front_len + back_len);
	if (front_len == ft_strlen(s1))
		ret_len = 0;
	ret = ft_substr(s1, front_len, ret_len);
	return (ret);
}
