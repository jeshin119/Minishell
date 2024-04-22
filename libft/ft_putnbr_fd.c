/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seunghan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 16:11:32 by seunghan          #+#    #+#             */
/*   Updated: 2023/11/08 17:12:43 by seunghan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

static void	put_n_max(long long n_max, int fd)
{
	char		nbr;
	long long	div;
	long long	size;

	size = n_max;
	div = 1;
	while (size > 9)
	{
		size = size / 10;
		div = div * 10;
	}
	while (div != 0)
	{
		nbr = n_max / div + 48;
		write(fd, &nbr, 1);
		n_max = n_max % div;
		div = div / 10;
	}
	return ;
}

void	ft_putnbr_fd(int n, int fd)
{
	long long	n_max;

	n_max = (long long)n;
	if (fd < 0)
		return ;
	if (!(n))
	{
		write(fd, "0", 1);
		return ;
	}
	if (n < 0)
	{
		n_max = -n_max;
		write(fd, "-", 1);
	}
	put_n_max(n_max, fd);
	return ;
}
