/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeshin <jeshin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 14:49:05 by jeshin            #+#    #+#             */
/*   Updated: 2024/05/22 19:29:25 by jeshin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	care_cd_error(char *path, char *home, char *new)
{
	if (path == NULL)
	{
		ft_putstr_fd("bash: cd: error retrieving current directory: ", 2);
		perror("getcwd: cannot access parent directories: ");
	}
	else
	{
		ft_putstr_fd("bash: cd: ", 2);
		ft_putstr_fd(path, 2);
		ft_putstr_fd(": ", 2);
		perror(NULL);
	}
	if (home != NULL)
		free(home);
	if (new != NULL)
		free(new);
	return (EXIT_FAILURE);
}

static char	*find_home_path(t_dq *env)
{
	char	*home;
	t_node	*start;

	start = env->head;
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

void	update_env_pwd(t_dq *env)
{
	t_node	*here;
	char	*pwd;
	char	cwd[1024];

	here = env->head;
	while (here)
	{
		if (!ft_strncmp(here->name, "PWD", 4))
		{
			pwd = here->val;
			here->val = ft_strdup(getcwd(cwd, 1024));
		}
		here = here->next;
	}
	here = env->head;
	while (here)
	{
		if (!ft_strncmp(here->name, "OLDPWD", 7))
		{
			if (here->val)
				free(here->val);
			here->val = pwd;
		}
		here = here->next;
	}
}

int	_cd(char *path, t_dq *env)
{
	char	*home;
	char	*new;
	char	check[4096];

	new = 0;
	home = find_home_path(env);
	if (path == 0 || !ft_strncmp(path, "-", 2) || \
	!ft_strncmp(path, "--", 3) || !ft_strncmp(path, "~", 2))
		path = home;
	if (!ft_strncmp(path, "~/", 2))
	{
		path++;
		new = ft_strjoin_no_free(home, path);
		path = new;
	}
	if (chdir(path) != EXIT_SUCCESS)
		return (care_cd_error(path, home, new));
	if (getcwd(check, sizeof(check)) == NULL)
		return (care_cd_error(NULL, home, new));
	update_env_pwd(env);
	if (home != NULL)
		free(home);
	if (new != NULL)
		free(new);
	return (EXIT_SUCCESS);
}
