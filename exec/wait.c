/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeshin <jeshin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 12:33:28 by jeshin            #+#    #+#             */
/*   Updated: 2024/05/21 12:00:08 by jeshin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	wait_childs(t_tree_info *info, t_dq *env)
{
	int			i;
	t_subtree	*subtree;

	subtree = info->sbt_lst->head;
	if (info->pipe_num == 0 && subtree && subtree->cmd)
	{
		if (is_builtin(subtree))
		{
			update_prev_status(env);
			return ;
		}
	}
	i = -1;
	while (++i < info->pipe_num + 1)
	{
		waitpid(-1, &(g_status), 0);
		if (WIFEXITED(g_status))
			g_status = WEXITSTATUS(g_status);
		else if (WIFSIGNALED(g_status))
			g_status = WTERMSIG(g_status) + 128;
		update_prev_status(env);
	}
}
