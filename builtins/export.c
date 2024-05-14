/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeshin <jeshin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 14:56:17 by jeshin            #+#    #+#             */
/*   Updated: 2024/05/14 12:07:43 by jeshin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	care_export_error(char *str)
{
	ft_putstr_fd("bash: export: ", 2);
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

static void	assign_variable_to_env(char *name, char *val, t_dq *env)
{
	t_node	*node;

	node = env->head;
	while (node)
	{
		if (ft_strncmp(node->name, name, ft_strlen(name) + 1) == 0)
		{
			if (node->val)
				free(node->val);
			node->val = val;
			return ;
		}
		node = node->next;
	}
	push_back_dq(env, name, val);
}

static int	ep(char *str, t_dq *env)
{
	char	*name;
	char	*val;
	int		i;

	i = -1;
	while (str[++i] && str[i] != '=')
		;
	name = ft_substr(str, 0, i);
	if (i == (int)ft_strlen(str))
		val = NULL;
	else
		val = ft_substr(str, i + 1, ft_strlen(str));
	if (ft_strncmp(name, "_", 2) == 0)
		return (EXIT_SUCCESS);
	if (has_name_err(name))
		return (care_export_error(str));
	assign_variable_to_env(name, val, env);
	return (EXIT_SUCCESS);
}

int	_export(char **opt, t_dq *env)
{
	int		status;
	int		i;

	status = 0;
	if (opt[1] == 0)
		return (status);
	i = 0;
	while (opt[++i])
	{
		if (opt[i][0] == '=')
		{
			status = care_export_error(opt[i]);
			continue ;
		}
		status = ep(opt[i], env);
	}
	return (status);
}
