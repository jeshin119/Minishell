/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeshin <jeshin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 18:10:25 by jeshin            #+#    #+#             */
/*   Updated: 2024/04/22 17:33:09 by jeshin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	mke_my_env(char **e, t_dq *env)
{
	char	**tmp;

	init_dq(env);
	while (*e)
	{
		tmp = ft_split(*e, '=');
		push_back_dq(env, tmp[0], tmp[1]);
		free(tmp);
		e++;
	}
}

void	_env(t_dq *env)
{
	t_node	*here;

	here = env->head;
	while (here)
	{
		ft_putstr(here->name);
		write(1, "=", 1);
		ft_putstr(here->val);
		write(1, "\n", 1);
		here = here->next;
	}
}
