/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeshin <jeshin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 20:08:54 by jeshin            #+#    #+#             */
/*   Updated: 2023/10/20 14:55:06 by jeshin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	len_dst;
	size_t	len_src;

	len_dst = 0;
	len_src = 0;
	while (*dst)
	{
		dst++;
		len_dst++;
	}
	while (src[len_src])
		len_src++;
	if (len_dst >= size)
		return (len_src + size);
	size = size - len_dst - 1;
	while (*src && size)
	{
		*dst = *src;
		src++;
		dst++;
		size--;
	}
	*dst = 0;
	return (len_dst + len_src);
}
