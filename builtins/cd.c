/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeshin <jeshin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 13:31:50 by jeshin            #+#    #+#             */
/*   Updated: 2024/05/04 12:52:37 by jeshin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "limits.h"

static int	care_cd_error(char *path)
{
	ft_putstr("bash: cd: ");
	ft_putstr(path);
	ft_putstr(": ");
	perror(NULL);
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

int	_cd(char *path,	t_dq *env)
{
	char	*home;
	char	*new;
	char	cur[1024];

	new = 0;
	home = find_home_path(env);
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
		return (care_cd_error(path));
	if (home != NULL)
		free(home);
	if (new != NULL)
		free(new);
	return (EXIT_SUCCESS);
}
