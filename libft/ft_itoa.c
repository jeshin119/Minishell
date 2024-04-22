/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeshin <jeshin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 18:56:14 by jeshin            #+#    #+#             */
/*   Updated: 2023/10/20 16:08:56 by jeshin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	check_digit(int n)
{
	int			len;
	long long	tmp;

	len = 0;
	tmp = (long long)n;
	if (!tmp)
		return (1);
	if (tmp < 0)
	{
		len++;
		tmp *= -1;
	}
	while (tmp)
	{
		len++;
		tmp /= 10;
	}
	return (len);
}

void	get_plus(long long *l, int *idx, int *flg, char *str)
{
	str[(*idx)++] = '-';
	*l *= -1;
	*flg = 0;
}

char	*ft_itoa(int n)
{
	char		*ret;
	int			len;
	int			i;
	long long	l;
	int			flg;

	len = check_digit(n);
	ret = (char *)malloc(sizeof(char) * (len + 1));
	if (!ret)
		return (0);
	l = (long long)n;
	i = 0;
	flg = 1;
	if (l < 0)
		get_plus(&l, &i, &flg, ret);
	while (i < len)
	{
		ret[len - i - flg] = l % 10 + '0';
		l /= 10;
		i++;
	}
	ret[len] = 0;
	return (ret);
}
