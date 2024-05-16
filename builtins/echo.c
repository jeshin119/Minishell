/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeshin <jeshin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 13:13:55 by jeshin            #+#    #+#             */
/*   Updated: 2024/05/16 19:08:56 by jeshin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	is_all_n(char *s)
{
	int	i;

	if (s == 0)
		return (FALSE);
	if (ft_strncmp(s, "-n", 3) == 0)
		return (TRUE);
	i = -1;
	if (s[++i] != '-')
		return (FALSE);
	while (s[++i])
	{
		if (s[i] != 'n')
			return (FALSE);
	}
	return (TRUE);
}

int	check_flg(char *str, int *flg, int *has_str)
{
	if (*has_str == 0)
	{
		if (is_all_n(str))
		{
			*flg = 1;
			return (EXIT_FAILURE);
		}
		else
			*has_str = 1;
	}
	return (EXIT_SUCCESS);
}

int	_echo(t_subtree *subtree)
{
	int	i;
	int	flg;
	int	has_str;

	if (subtree->opt_size == 0)
	{
		write(1, "\n", 1);
		return (EXIT_SUCCESS);
	}
	i = 0;
	has_str = 0;
	flg = 0;
	while (++i < subtree->opt_size)
	{
		if (check_flg((subtree->opt)[i], &flg, &has_str))
			continue ;
		if ((subtree->opt)[i] == 0)
			continue;
		ft_putstr((subtree->opt[i]));
		if ((subtree->opt[i + 1]) != 0)
			write(1, " ", 1);
	}
	if (!flg)
		write(1, "\n", 1);
	return (EXIT_SUCCESS);
}
