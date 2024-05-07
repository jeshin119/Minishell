/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_puthex_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeshin <jeshin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 17:14:58 by jeshin            #+#    #+#             */
/*   Updated: 2023/12/09 18:34:08 by jeshin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_puthex_fd(long int n, int fd, int upper)
{
	long int			l;
	char				*set;

	l = (long int)n;
	if (upper)
		set = "0123456789ABCDEF";
	else
		set = "0123456789abcdef";
	if (l < 0)
	{
		l *= -1;
		write(fd, "-", 1);
	}
	if (l < 16)
		write(fd, &set[l], 1);
	else if (l >= 16)
	{
		ft_puthex_fd(l / 16, 1, upper);
		write(fd, &set[l % 16], 1);
	}
}

void	ft_puthex_cnt(unsigned long int n, int upper, int *num)
{
	unsigned long int	l;
	char				*set;

	l = (unsigned long int)n;
	if (upper)
		set = "0123456789ABCDEF";
	else
		set = "0123456789abcdef";
	if (l < 0)
	{
		l *= -1;
		*num += write(1, "-", 1);
	}
	if (l < 16)
		*num += write(1, &set[l], 1);
	else if (l >= 16)
	{
		ft_puthex_cnt(l / 16, upper, num);
		*num += write(1, &set[l % 16], 1);
	}
}
