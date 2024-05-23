/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeshin <jeshin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 12:33:28 by jeshin            #+#    #+#             */
/*   Updated: 2024/05/23 14:59:35 by jeshin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	update_child_status(int *redundant, t_dq *env)
{
	if (WIFEXITED(g_status))
	{
		g_status = WEXITSTATUS(g_status);
		update_prev_status(env);
	}
	if (WIFSIGNALED(g_status))
	{
		if (!(*redundant) && g_status == SIGINT)
		{
			if (*redundant == 0)
				*redundant = 1;
			write(2, "\n", 1);
		}
		if (!(*redundant) && g_status == SIGQUIT)
		{
			if (*redundant == 0)
				*redundant = 1;
			write(2, "QUIT: 3\n", 8);
		}
		g_status = WTERMSIG(g_status) + 128;
		update_prev_status(env);
	}
}

void	wait_childs(t_tree_info *info, t_dq *env)
{
	int			i;
	int			redundant;
	t_subtree	*subtree;

	subtree = info->sbt_lst->head;
	if (info->pipe_num == 0 && subtree && is_builtin(subtree))
	{
		update_prev_status(env);
		return ;
	}
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	i = -1;
	redundant = 0;
	while (++i < info->pipe_num + 1)
	{
		waitpid(-1, &(g_status), 0);
		update_child_status(&redundant, env);
	}
	set_signal_in_main();
}
