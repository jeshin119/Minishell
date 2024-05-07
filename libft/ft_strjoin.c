/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seunghan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 13:32:10 by seunghan          #+#    #+#             */
/*   Updated: 2024/04/25 14:38:56 by seunghan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

static void	free_args(char *s1, char *s2)
{
	free(s1);
	free(s2);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*ret;
	size_t	s1_len;
	size_t	s2_len;

	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	ret = (char *)malloc((s1_len + s2_len) * sizeof(char) + 1);
	if (!ret)
		exit(1);
	s1_len = 0;
	while (s1[s1_len])
	{
		ret[s1_len] = s1[s1_len];
		s1_len++;
	}
	s2_len = 0;
	while (s2[s2_len])
	{
		ret[s1_len] = s2[s2_len];
		s1_len++;
		s2_len++;
	}
	ret[s1_len] = 0;
	free_args(s1, s2);
	return (ret);
}
