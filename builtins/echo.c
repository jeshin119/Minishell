/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeshin <jeshin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 13:13:55 by jeshin            #+#    #+#             */
/*   Updated: 2024/05/03 10:23:20 by jeshin           ###   ########.fr       */
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

	i = 0;
	if ((subtree->opt)[i + 1] == 0)
	{
		write(1, "\n", 1);
		return (EXIT_SUCCESS);
	}
	has_str = 0;
	flg = 0;
	while ((subtree->opt)[++i])
	{
		if (check_flg((subtree->opt)[i], &flg, &has_str))
			continue ;
		ft_putstr((subtree->opt[i]));
		if ((subtree->opt[i + 1]) != 0)
			write(1, " ", 1);
	}
	if (!flg)
		write(1, "\n", 1);
	return (EXIT_SUCCESS);
}
