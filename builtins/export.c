/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeshin <jeshin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 14:56:17 by jeshin            #+#    #+#             */
/*   Updated: 2024/05/16 16:52:17 by jeshin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	care_export_error(char *name, char *val)
{
	if (ft_strncmp(name, "_", 2) == EXIT_SUCCESS)
	{
		if (name)
			free(name);
		if (val)
			free(val);
		return (EXIT_SUCCESS);
	}
	ft_putstr_fd("bash: export: ", 2);
	ft_putstr_fd("`", 2); if (name && *name)
		ft_putstr_fd(name, 2);
	else
		ft_putstr_fd(val, 2);
	ft_putstr_fd("': ", 2);
	ft_putstr_fd("not a vaild identifier\n", 2);
	if (name)
		free(name);
	if (val)
		free(val);
	return (EXIT_FAILURE);
}

static int	has_name_err(char *name)
{
	int	has_letter;

	if (name == 0 || *name == 0)
		return (TRUE);
	if (*name == '_' && *(name + 1) == 0)
		return (TRUE);
	has_letter = 0;
	while (*name)
	{
		if (has_letter == 0 && ft_isdigit(*name))
			return (TRUE);
		if (!ft_isalnum(*name) && *name != '_')
			return (TRUE);
		if (*name == 32 || (*name >= 9 && *name <= 13))
			return (TRUE);
		if (ft_isalpha(*name))
			has_letter = 1;
		name++;
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
			if (name)
				free(name);
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
	if (str && *str == '=')
		return (care_export_error(NULL, ft_strdup(str)));
	while (str[++i] && str[i] != '=')
		;
	name = ft_substr(str, 0, i);
	if (i == (int)ft_strlen(str))
		val = NULL;
	else
		val = ft_substr(str, i + 1, ft_strlen(str));
	if (has_name_err(name) == TRUE)
		return (care_export_error(name, val));
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
		status = ep(opt[i], env);
	return (status);
}
