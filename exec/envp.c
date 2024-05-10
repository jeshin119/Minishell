/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeshin <jeshin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 13:05:41 by jeshin            #+#    #+#             */
/*   Updated: 2024/05/10 13:27:58 by jeshin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	add_prev_status_env(t_dq *env)
{
	push_back_dq(env, ft_strdup("?"), ft_itoa(0));
}

static void	reset_oldpwd_env(t_dq *env)
{
	t_node	*start;

	start = env->head;
	while (start)
	{
		if (!ft_strncmp(start->name, "OLDPWD", 7))
		{
			if (start->val)
				free(start->val);
			start->val = 0;
			return ;
		}
		start = start->next;
	}
}

void	make_my_env(char **e, t_dq *env)
{
	char	**tmp;

	init_dq(env);
	while (*e)
	{
		tmp = ft_split(*e, '=');
		push_back_dq(env, ft_strdup(tmp[0]), ft_strdup(tmp[1]));
		free_tab(tmp);
		e++;
	}
	add_prev_status_env(env);
	reset_oldpwd_env(env);
}

char	**get_envtab(t_dq *env)
{
	char	**tab;
	t_node	*start;
	char	*tmp;
	int		i;

	start = env->head;
	tab = (char **)malloc(sizeof(char *) * (env->size + 1));
	i = -1;
	while (start && i < env->size)
	{
		if (start->name == 0 || start->val == 0)
		{
			start = start->next;
			i++;
			continue ;
		}
		tmp = ft_strjoin_no_free(start->name, "=");
		tab[++i] = ft_strjoin_no_free(tmp, start->val);
		free(tmp);
		start = start->next;
	}
	tab[env->size] = 0;
	return (tab);
}
