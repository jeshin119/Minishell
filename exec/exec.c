/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeshin <jeshin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 14:26:06 by jeshin            #+#    #+#             */
/*   Updated: 2024/05/18 14:44:08 by jeshin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	exec_tree(t_tree *tree, t_dq *env)
{
	t_tree_info	tree_info;

	init_tree_info(tree, &tree_info);
	if (mke_subtree_lst(tree, &tree_info, env) == EXIT_FAILURE)
	{
		reset_tree_info(&tree_info);
		return (EXIT_FAILURE);
	}
	open_pipes((tree_info.pipe_num), &(tree_info.pipe_tab));
	go_exec(&tree_info, env);
	close_all_pipe(tree_info.pipe_num, tree_info.pipe_tab);
	wait_childs(&tree_info, env);
	reset_tree_info(&tree_info);
	return (EXIT_SUCCESS);
}
