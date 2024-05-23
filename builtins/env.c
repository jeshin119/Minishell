/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeshin <jeshin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 18:10:25 by jeshin            #+#    #+#             */
/*   Updated: 2024/05/23 18:23:00 by jeshin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	_env(t_dq *env)
{
	t_node	*here;

	here = env->head;
	while (here)
	{
		if (here->val == 0)
			;
		else if (ft_strncmp(here->name, "?", 2) == EXIT_SUCCESS)
			;
		else if (ft_strncmp(here->name, "~", 2) == EXIT_SUCCESS)
			;
		else
			printf("%s=%s\n", here->name, here->val);
		here = here->next;
	}
	return (EXIT_SUCCESS);
}
