/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeshin <jeshin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 13:13:55 by jeshin            #+#    #+#             */
/*   Updated: 2024/05/01 18:53:14 by jeshin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	_echo(t_subtree *subtree)
{
	int		i;

	i = -1;
	while ((subtree->opt)[++i])
		;
	if (i == 1)
		ft_putstr("\n");
	else if (i == 2 && ft_strncmp((subtree->opt)[1], "-n", 3) == 0)
		;
	else if (i == 2 && ft_strncmp((subtree->opt)[1], "-n", 3))
	{	
		ft_putstr(subtree->opt[1]);
		write(1, "\n", 1);
	}
	else if (i == 3 && ft_strncmp((subtree->opt)[1], "-n", 3) == 0)
		ft_putstr(subtree->opt[2]);
	exit(EXIT_SUCCESS);
}
