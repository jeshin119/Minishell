/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeshin <jeshin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 12:33:28 by jeshin            #+#    #+#             */
/*   Updated: 2024/05/09 13:18:52 by jeshin           ###   ########.fr       */
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
			update_prev_status(env, g_status);
			return ;
		}
	}
	i = -1;
	while (++i < info->pipe_num + 1)
	{
		waitpid(-1, &g_status, 0);
		if (WIFEXITED(g_status))
			update_prev_status(env, WEXITSTATUS(g_status));
		else if (WIFSIGNALED(g_status))
			update_prev_status(env, WTERMSIG(g_status) + 128);
	}
}
