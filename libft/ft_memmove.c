/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeshin <jeshin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 19:16:11 by jeshin            #+#    #+#             */
/*   Updated: 2023/10/21 18:21:17 by jeshin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	move_from_front(void *dst, const void *src, size_t *len)
{
	size_t			prv;

	while (*len)
	{
		*(unsigned char *)dst++ = *(unsigned char *)src++;
		prv = (*len)--;
		if (*len > prv)
			break ;
	}
}

void	move_from_back(void *dst, const void *src, size_t *len)
{
	size_t			prv;

	while (*len)
	{
		*(unsigned char *)(dst + *len - 1) = *(unsigned char *)(src + *len - 1);
		prv = (*len)--;
		if (*len > prv)
			break ;
	}
}

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	void	*ret;

	ret = dst;
	if (dst < src)
		move_from_front(dst, src, &len);
	else if (dst > src)
		move_from_back(dst, src, &len);
	return (dst);
}
