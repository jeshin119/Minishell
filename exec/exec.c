/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeshin <jeshin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 14:26:06 by jeshin            #+#    #+#             */
/*   Updated: 2024/05/20 12:55:36 by jeshin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	exec_tree(char *buf, t_tree *tree, t_dq *env)
{
	t_tree_info	tree_info;

	init_tree_info(tree, &tree_info);
	if (mke_subtree_lst(buf, tree, &tree_info, env) == EXIT_FAILURE)
	{
		reset_tree_info(&tree_info);
		return (EXIT_FAILURE);
	}
	open_pipes((tree_info.pipe_num), &(tree_info.pipe_tab));
	exec_cmds(&tree_info, env);
	close_all_pipe(tree_info.pipe_num, tree_info.pipe_tab);
	wait_childs(&tree_info, env);
	reset_tree_info(&tree_info);
	return (EXIT_SUCCESS);
}
