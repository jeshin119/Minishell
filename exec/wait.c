/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeshin <jeshin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 12:33:28 by jeshin            #+#    #+#             */
/*   Updated: 2024/05/13 14:45:04 by jeshin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	wait_childs(t_tree_info *info)
{
	int			i;
	t_subtree	*subtree;

	subtree = info->sbt_lst->head;
	if (info->pipe_num == 0 && subtree && subtree->cmd)
	{
		if (is_builtin(subtree))
		{
			update_prev_status(g_env.status);
			return ;
		}
	}
	i = -1;
	while (++i < info->pipe_num + 1)
	{
		waitpid(-1, &(g_env.status), 0);
		if (WIFEXITED(g_env.status))
			update_prev_status(WEXITSTATUS(g_env.status));
		else if (WIFSIGNALED(g_env.status))
			update_prev_status(WTERMSIG(g_env.status) + 128);
	}
}
