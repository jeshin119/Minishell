/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeshin <jeshin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 17:01:00 by jeshin            #+#    #+#             */
/*   Updated: 2024/05/15 15:58:10 by jeshin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	care_unset_error(char *str)
{
	ft_putstr_fd("bash: unset: ", 2);
	ft_putstr_fd("`", 2);
	if (*str)
		ft_putstr_fd(str, 2);
	ft_putstr_fd("': ", 2);
	ft_putstr_fd("not a vaild identifier\n", 2);
	return (EXIT_FAILURE);
}

static int	has_name_err(char *s)
{
	int	has_letter;

	has_letter = 0;
	while (*s)
	{
		if (has_letter == 0 && ft_isdigit(*s))
			return (TRUE);
		if (!ft_isalnum(*s) && *s != '_')
			return (TRUE);
		if (*s == 32 || (*s >= 9 && *s <= 13))
			return (TRUE);
		if (ft_isalpha(*s))
			has_letter = 1;
		s++;
	}
	return (FALSE);
}

static int	free_node(t_node *this)
{
	if (this->name != 0)
		free(this->name);
	if (this->val != 0)
		free(this->val);
	free(this);
	return (EXIT_SUCCESS);
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
		if (has_name_err(opt[i]))
		{
			care_unset_error(opt[i]);
			continue ;
		}
		start = env->head;
		while (start)
		{
			if (ft_strncmp(start->name, opt[i], ft_strlen(opt[i]) + 1) == 0)
			{
				organize_node(start, env);
				return (free_node(start));
			}
			start = start->next;
		}
	}
	return (EXIT_SUCCESS);
}
