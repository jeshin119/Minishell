/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeshin <jeshin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 16:45:45 by jeshin            #+#    #+#             */
/*   Updated: 2024/05/15 19:40:08 by jeshin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static char	**get_path_tab(t_dq *env)
{
	t_node	*start;
	char	**tab;
	char	*tmp;
	int		i;

	start = env->head;
	while (start)
	{
		if (ft_strncmp(start->name, "PATH", 4) == 0)
			break ;
		start = start->next;
	}
	if (start == NULL)
		return (NULL);
	tab = ft_split(start->val, ':');
	i = -1;
	while (tab[++i])
	{
		tmp = ft_strjoin_no_free(tab[i], "/");
		free(tab[i]);
		tab[i] = tmp;
	}
	return (tab);
}

static int	ret_path(char **cmd, t_dq *env)
{
	int		i;
	char	*path;
	char	**tab;

	if (*cmd == 0)
		return (EXIT_FAILURE);
	tab = get_path_tab(env);
	i = -1;
	while (tab && tab[++i])
	{
		path = ft_strjoin_no_free(tab[i], *cmd);
		if (access(path, F_OK | X_OK) == 0)
		{
			free_tab(tab);
			free(*cmd);
			*cmd = path;
			return (EXIT_SUCCESS);
		}
		free(path);
	}
	free_tab(tab);
	return (EXIT_FAILURE);
}

static int	check_path(char *path)
{
	struct stat	statbuf;

	stat(path, &statbuf);
	if (S_ISDIR(statbuf.st_mode))
	{
		ft_putstr_fd(path, 2);
		ft_putstr_fd(": is a directory\n", 2);
		exit(126);
		return (EXIT_FAILURE);
	}
	if (!S_ISDIR(statbuf.st_mode) && !S_ISREG(statbuf.st_mode))
	{
		ft_putstr_fd(path, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		exit(127);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int	get_path(char **cmd, t_dq *env)
{
	int			i;
	int			absolute_flg;

	if (*cmd == 0 || **cmd == 0)
		return (put_command_not_found(*cmd));
	i = -1;
	absolute_flg = 0;
	while ((*cmd)[++i])
	{
		if (absolute_flg == 0 && ft_isspace((*cmd)[i]))
			break ;
		if ((*cmd)[i] == '/')
		{
			absolute_flg++;
			break ;
		}
	}
	if (absolute_flg)
		return (check_path(*cmd));
	if (ret_path(cmd, env))
		return (put_command_not_found(*cmd));
	return (EXIT_SUCCESS);
}
