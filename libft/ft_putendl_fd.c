/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seunghan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 15:55:04 by seunghan          #+#    #+#             */
/*   Updated: 2023/11/08 17:17:29 by seunghan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

void	ft_putendl_fd(char *s, int fd)
{
	size_t	size;

	size = ft_strlen(s);
	if (fd >= 0)
	{
		write(fd, s, size);
		write(fd, "\n", 1);
	}
	return ;
}
