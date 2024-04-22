/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeshin <jeshin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 13:31:50 by jeshin            #+#    #+#             */
/*   Updated: 2024/04/22 15:23:01 by jeshin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	take_cd_error(char *path)
{
	ft_putstr("bash: cd: ");
	ft_putstr(path);
	ft_putstr(": ");
	perror("");
	return (EXIT_FAILURE);
}

static char	*find_home_path(t_dq *env)
{
	char	*home;
	t_node	*start;

	while (start)
	{
		if (ft_strncmp(start->name, "HOME=", 5) == 0)
			home = ft_substr(start->name, 5, ft_strlen(start->name) - 5);
		start = start->next;
	}
	return (home);
}

int	_cd(char *path,	t_dq *env)
{
	char	*home;
	char	*new;

	if (*path == 0)
		return (EXIT_SUCCESS);
	home = find_home_path(env);
	if (path == 0 || !ft_strncmp(path, "-", 2) || \
	!ft_strncmp(path, "--", 3) || !ft_strncmp(path, "~", 2))
	{
		if (chdir(home) == -1)
			exit(take_cd_error(path));
	}
	if (!ft_strncmp(path, "~/", 2))
	{
		path += 2;
		new = ft_strjoin(home, path);
	}
	else
	{
		if (chdir(path) == -1)
			exit(take_cd_error(path));
	}
	return (EXIT_SUCCESS);
}
