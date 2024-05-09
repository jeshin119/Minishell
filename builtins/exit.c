/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeshin <jeshin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 17:31:11 by jeshin            #+#    #+#             */
/*   Updated: 2024/05/09 15:52:06 by jeshin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	has_opt_err(char *s)
{
	int	has_space;
	int	has_num;

	has_space = 0;
	has_num = 0;
	while (*s)
	{
		if (!ft_isdigit(*s) && !ft_isspace(*s))
			return (TRUE);
		if (has_num == 1 && has_space == 1 && !ft_isspace(*s))
			return (TRUE);
		if (ft_isdigit(*s))
			has_num = 1;
		if (ft_isspace(*s))
			has_space = 1;
		s++;
	}
	if (has_num == 0)
		return (TRUE);
	return (FALSE);
}

int	_bexit_(char **opt)
{
	int	i;
	int	j;

	i = -1;
	while (opt[++i])
		;
	printf("exit\n");
	if (i == 1)
		exit(EXIT_SUCCESS);
	if (has_opt_err(opt[1]))
	{
		ft_putstr_fd("bash: exit: ", 2);
		ft_putstr_fd(opt[1], 2);
		ft_putstr_fd(": numeric argument required\n", 2);
		exit(255);
	}
	if (i == 2)
		exit(ft_atoi(opt[1]));
	if (i > 2)
	{
		ft_putstr_fd("bash: exit: too many arguments\n", 2);
		g_status = 1;
		return (EXIT_FAILURE);
	}
	return (EXIT_FAILURE);
}

int	_exit_(char **opt)
{
	int	i;
	int	j;

	i = -1;
	while (opt[++i])
		;
	if (i == 1)
		exit(EXIT_SUCCESS);
	if (has_opt_err(opt[1]))
	{
		ft_putstr_fd("bash: exit: ", 2);
		ft_putstr_fd(opt[1], 2);
		ft_putstr_fd(": numeric argument required\n", 2);
		exit(255);
	}
	if (i == 2)
		exit(ft_atoi(opt[1]));
	if (i > 2)
	{
		ft_putstr_fd("bash: exit: too many arguments\n", 2);
		exit(EXIT_FAILURE);
	}
	return (EXIT_FAILURE);
}
