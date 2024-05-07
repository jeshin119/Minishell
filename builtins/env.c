/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeshin <jeshin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 18:10:25 by jeshin            #+#    #+#             */
/*   Updated: 2024/05/04 15:31:11 by jeshin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	_env(t_dq *env)
{
	t_node	*here;

	here = env->head;
	while (here)
	{
		if (here->val)
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
