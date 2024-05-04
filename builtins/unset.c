/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeshin <jeshin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 17:01:00 by jeshin            #+#    #+#             */
/*   Updated: 2024/05/04 15:28:53 by jeshin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

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

int	_unset(char **opt, t_dq *env)
{
	t_node	*start;
	int		i;

	i = 0;
	while (opt[++i])
	{
		start = env->head;
		while (start)
		{
			if (ft_strncmp(start->name, opt[i], ft_strlen(opt[i]) + 1) == 0)
			{
				organize_node(start, env);
				free_node(start);
			}
			start = start->next;
		}
	}
	return (EXIT_SUCCESS);
}
