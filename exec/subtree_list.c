/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subtree_list.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeshin <jeshin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 17:37:32 by jeshin            #+#    #+#             */
/*   Updated: 2024/05/22 11:30:16 by jeshin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	create_and_link_subtree(t_tree *tree, t_tree_info *info, t_dq *env)
{
	t_subtree	*new;

	if (create_subtree(tree, &new, env) == EXIT_FAILURE)
		info->pipe_num--;
	if (link_subtree(&(info->sbt_lst), new) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	make_subtree_list(t_tree *tree, t_tree_info *info, t_dq *env)
{
	if (g_status == SIGINT)
		return (EXIT_FAILURE);
	if (tree->ctrl_token != PIPE)
		return (create_and_link_subtree(tree, info, env));
	if (tree->ctrl_token == PIPE && tree->next_left && tree->next_right == 0)
	{
		if (create_and_link_subtree(tree, info, env) == EXIT_FAILURE)
			return (EXIT_FAILURE);
		if (add_pipe_input(info, tree, tree->tk_list) == EXIT_FAILURE)
			return (EXIT_FAILURE);
		return (make_subtree_list(tree->next_right, info, env));
	}
	if (tree->ctrl_token == PIPE && tree->next_left && tree->next_right)
	{
		if (create_and_link_subtree(tree, info, env) == EXIT_FAILURE)
			return (EXIT_FAILURE);
		return (make_subtree_list(tree->next_right, info, env));
	}
	return (EXIT_FAILURE);
}
