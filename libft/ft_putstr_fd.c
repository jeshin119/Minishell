/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeshin <jeshin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 15:48:20 by seunghan          #+#    #+#             */
/*   Updated: 2024/04/22 17:35:50 by jeshin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

size_t	ft_putstr_fd(char *s, int fd)
{
	size_t	size;

	size = ft_strlen(s);
	if (fd >= 0)
		return (write(fd, s, size));
	return (0);
}

size_t	ft_putstr(char *s)
{
	size_t	size;

	size = ft_strlen(s);
	return (write(1, s, size));
}