/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeshin <jeshin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 17:01:00 by jeshin            #+#    #+#             */
/*   Updated: 2024/05/01 15:57:06 by jeshin           ###   ########.fr       */
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

static void	free_node(t_node *this)
{
	if (this->name != 0)
		free(this->name);
	if (this->val != 0)
		free(this->val);
	free(this);
}

static void	organize_node(t_node *this, t_dq *env)
{
	if (this == env->tail)
	{
		this->prev->next = 0;
		env->tail = this->prev;
	}
	else if (this == env->head)
	{
		this->next->prev = 0;
		env->head = this->next;
	}
	else
	{
		this->prev->next = this->next;
		this->next->prev = this->prev;
	}
}

void	_unset(t_dq *env, char *remove)
{
	t_node	*start;

	start = env->head;
	while (start)
	{
		if (ft_strncmp(start->name, remove, ft_strlen(remove) + 1) == 0)
		{
			organize_node(start, env);
			free_node(start);
			return ;
		}
		start = start->next;
	}
	exit(EXIT_SUCCESS);
}
