/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeshin <jeshin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 15:06:57 by jeshin            #+#    #+#             */
/*   Updated: 2024/06/03 17:37:20 by jeshin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	care_cd_error(char *path, int relative)
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
	if (relative)
		_free(path);
	return (EXIT_FAILURE);
}

static void	update_env_pwd(t_dq *env)
{
	t_node	*node;
	char	*pwd;
	char	cwd[4096];

	node = get_node_from_env("PWD", env);
	if (node == 0)
	{
		pwd = NULL;
		push_back_dq(env, ft_strdup("PWD"), \
		ft_strdup(getcwd(cwd, sizeof(cwd))));
	}
	else
	{
		pwd = node->val;
		node->val = ft_strdup(getcwd(cwd, sizeof(cwd)));
	}
	node = get_node_from_env("OLDPWD", env);
	if (node == 0)
		push_back_dq(env, ft_strdup("OLDPWD"), pwd);
	else
	{
		if (node->val)
			free(node->val);
		node->val = pwd;
	}
}

static int	chdir_to_oldpwd(t_dq *env)
{
	char		cur[4096];
	t_node		*here;

	here = get_node_from_env("OLDPWD", env);
	if (here == NULL || here->val == NULL)
	{
		ft_putstr_fd("bash: cd: OLDPWD not set\n", 2);
		return (EXIT_FAILURE);
	}
	if (chdir(here->val) != EXIT_SUCCESS)
		return (care_cd_error(here->val, 0));
	printf("bash: cd: %s\n", getcwd(cur, sizeof(cur)));
	update_env_pwd(env);
	return (EXIT_SUCCESS);
}

static int	check_relative_path(char **path, t_dq *env)
{
	char		*home;
	t_node		*node;

	node = get_node_from_env("~", env);
	home = ft_strdup(node->val);
	if (*path == 0 || !ft_strncmp(*path, "--", 3) || !ft_strncmp(*path, "~", 2))
	{
		*path = home;
		return (EXIT_SUCCESS);
	}
	else if (!ft_strncmp(*path, "~/", 2))
	{
		(*path)++;
		(*path) = ft_strjoin_no_free(home, (*path));
		_free(home);
		return (EXIT_SUCCESS);
	}
	_free(home);
	return (EXIT_FAILURE);
}

int	_cd(char *path, t_dq *env)
{
	char		cur[4096];
	int			relative;

	relative = 0;
	if (check_relative_path(&path, env) == EXIT_SUCCESS)
		relative = 1;
	else if (!ft_strncmp(path, "-", 2))
		return (chdir_to_oldpwd(env));
	if (chdir(path) != EXIT_SUCCESS)
		return (care_cd_error(path, relative));
	if (getcwd(cur, sizeof(cur)) == NULL)
		return (care_cd_error(NULL, relative));
	update_env_pwd(env);
	if (relative)
		_free(path);
	return (EXIT_SUCCESS);
}
