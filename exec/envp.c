/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeshin <jeshin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 13:05:41 by jeshin            #+#    #+#             */
/*   Updated: 2024/06/03 19:03:49 by jeshin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	add_status_env(t_dq *env)
{
	t_node	*here;

	here = env->head;
	while (here)
	{
		if (ft_strncmp(here->name, "?", 2) == 0)
			return ;
		here = here->next;
	}
	push_back_dq(env, ft_strdup("?"), ft_itoa(0));
}

static void	add_home_env(t_dq *env)
{
	t_node	*here;

	here = env->head;
	while (here)
	{
		if (ft_strncmp(here->name, "~", 2) == 0)
			return ;
		here = here->next;
	}
	push_back_dq(env, ft_strdup("~"), getenv("HOME"));
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
	char	*name;
	char	*val;
	char	*divider;
	int		name_size;

	init_dq(env);
	while (*e)
	{
		divider = ft_strchr(*e, '=');
		if (divider == 0)
		{
			e++;
			continue ;
		}
		name_size = (int)(divider - *e);
		name = ft_substr(*e, 0, name_size);
		val = ft_substr(*e, name_size + 1, ft_strlen(*e) - name_size);
		push_back_dq(env, name, val);
		e++;
	}
	add_status_env(env);
	add_home_env(env);
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
		tmp = ft_strjoin_no_free(start->name, "=");
		tab[++i] = ft_strjoin_no_free(tmp, start->val);
		free(tmp);
		start = start->next;
	}
	tab[env->size] = 0;
	return (tab);
}
