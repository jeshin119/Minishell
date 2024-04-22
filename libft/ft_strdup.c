/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seunghan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 16:56:05 by seunghan          #+#    #+#             */
/*   Updated: 2023/11/08 12:03:56 by seunghan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include<stdlib.h>

char	*ft_strdup(const char *s1)
{
	char	*str;
	size_t	i;
	size_t	count;

	i = 0;
	count = 0;
	while (s1[count])
		count++;
	str = (char *)malloc(sizeof(char) * count + 1);
	if (str == 0)
		return (0);
	while (i < count + 1)
	{
		str[i] = s1[i];
		i++;
	}
	return (str);
}
