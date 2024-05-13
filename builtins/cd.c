/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeshin <jeshin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 14:49:05 by jeshin            #+#    #+#             */
/*   Updated: 2024/05/13 15:14:00 by jeshin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	care_cd_error(char *path)
{
	ft_putstr("bash: cd: ");
	ft_putstr(path);
	ft_putstr(": ");
	perror(NULL);
	return (EXIT_FAILURE);
}

static char	*find_home_path(void)
{
	char	*home;
	t_node	*start;

	start = g_env.head;
	while (start)
	{
		if (ft_strncmp(start->name, "HOME", 5) == 0)
		{
			home = ft_substr(start->val, 0, ft_strlen(start->val));
			return (home);
		}
		start = start->next;
	}
	return (NULL);
}

void	update_env_pwd(char *path)
{
	t_node	*go_pwd;
	t_node	*go_old;
	char	*pwd;

	go_pwd = g_env.head;
	while (go_pwd)
	{
		if (!ft_strncmp(go_pwd->name, "PWD", 4))
		{
			pwd = go_pwd->val;
			go_pwd->val = path;
		}
		go_pwd = go_pwd->next;
	}
	go_old = g_env.head;
	while (go_old)
	{
		if (!ft_strncmp(go_pwd->name, "OLDPWD", 7))
		{
			if (go_old->val)
				free(go_old->val);
			go_old->val = pwd;
		}
		go_old = go_old->next;
	}
}

int	_cd(char *path)
{
	char	*home;
	char	*new;

	new = 0;
	home = find_home_path();
	if (path == 0 || !ft_strncmp(path, "-", 2) || \
	!ft_strncmp(path, "--", 3) || !ft_strncmp(path, "~", 2))
		path = home;
	else if (!ft_strncmp(path, "~/", 2))
	{
		path++;
		new = ft_strjoin_no_free(home, path);
		path = new;
	}
	if (chdir(path) != 0)
	{
		update_env_pwd(path);
		return (care_cd_error(path));
	}
	if (home != NULL)
		free(home);
	if (new != NULL)
		free(new);
	return (EXIT_SUCCESS);
}
