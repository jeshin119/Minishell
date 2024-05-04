/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeshin <jeshin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 14:56:17 by jeshin            #+#    #+#             */
/*   Updated: 2024/05/04 14:57:32 by jeshin           ###   ########.fr       */
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

static int	ep(char *str, t_dq *env)
{
	char	*name;
	char	*val;
	int		i;

	i = -1;
	while (str[++i] && str[i] != '=')
		;
	name = ft_substr(str, 0, i);
	if (i == ft_strlen(str))
		val = NULL;
	else
		val = ft_substr(str, i + 1, ft_strlen(str));
	if (ft_strncmp(name, "_", 2) == 0)
		return (EXIT_SUCCESS);
	if (has_name_err(name))
		return (care_export_error(str));
	push_back_dq(env, name, val);
	return (EXIT_SUCCESS);
}

int	_export(char **opt, t_dq *env)
{
	int	state;
	int	i;

	state = 0;
	if (opt[1] == 0)
		return (state);
	i = 0;
	while (opt[++i])
	{
		if (!state)
			state = ep(opt[i], env);
		else
			ep(opt[i], env);
	}
	return (state);
}
