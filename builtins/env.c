/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeshin <jeshin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 18:10:25 by jeshin            #+#    #+#             */
/*   Updated: 2024/05/14 12:08:15 by jeshin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	_env(t_dq *env)
{
	t_node	*here;

	here = env->head;
	while (here)
	{
		if (here->val && ft_strncmp(here->name, "?", 2) != EXIT_SUCCESS)
		{
			ft_putstr(here->name);
			write(1, "=", 1);
			ft_putstr(here->val);
			write(1, "\n", 1);
		}
		here = here->next;
	}
	return (EXIT_SUCCESS);
}
