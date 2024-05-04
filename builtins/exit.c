/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeshin <jeshin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 17:31:11 by jeshin            #+#    #+#             */
/*   Updated: 2024/05/07 13:25:01 by jeshin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	_exit_(char **opt)
{
	int	i;
	int	j;

	i = -1;
	while (opt[++i])
		;
	if (i == 1)
	{
		printf("exit\n");
		exit(EXIT_SUCCESS);
	}
	else if (i == 2)
	{
		printf("exit\n");
		exit(ft_atoi(opt[1]));
	}
	else
	{
		j = -1;
		while (opt[1][++j] && ft_isdigit(opt[1][j]))
			;
		if (opt[1][j])
		{
			printf("bash: exit: %s: numeric argument required\n",opt[1]);
			exit(255);
		}
		printf("bash: exit: too many arguments\n");
		exit(ft_atoi(opt[1]));
	}
	return (1);
}
