/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeshin <jeshin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 10:38:21 by seunghan          #+#    #+#             */
/*   Updated: 2024/05/04 16:29:53 by jeshin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

size_t	ft_strlen(const char *str)
{
	int	i;

	i = 0;
	while (*str)
	{
		i++;
		str++;
	}
	return (i);
}

size_t	ft_strlen_js(const char *s)
{
	size_t	i;

	i = 0;
	if (s == 0)
		return (0);
	while (*s)
	{
		s++;
		i++;
	}
	return (i);
}
