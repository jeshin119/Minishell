/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeshin <jeshin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 18:11:23 by jeshin            #+#    #+#             */
/*   Updated: 2024/05/08 18:44:58 by jeshin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	get_infile_fd(t_subtree *subtree)
{
	if (subtree == 0)
		return (STDIN_FILENO);
	if (subtree->infile == NULL)
		return (STDIN_FILENO);
	if (subtree->is_heredoc == ON)
		return (open_infile_n_return(subtree));
	if (subtree->is_heredoc == OFF && subtree->infile != NULL)
		return (open_infile_n_return(subtree));
	return (STDIN_FILENO);
}

int	get_outfile_fd(t_subtree *subtree)
{
	if (subtree == 0)
		return (STDOUT_FILENO);
	if (subtree->outfile == NULL)
		return (STDOUT_FILENO);
	if (subtree->is_appending == ON)
		return (open_appending_n_return(subtree));
	if (subtree->is_appending == OFF && subtree->outfile != NULL)
		return (open_outfile_n_return(subtree));
	return (STDOUT_FILENO);
}

int	get_file_name(t_tree *tree, t_subtree *subtree)
{
	if (tree == 0)
		return (EXIT_SUCCESS);
	if (subtree == 0)
		return (EXIT_FAILURE);
	if (tree->ctrl_token == PIPE)
		return (EXIT_SUCCESS);
	if (tree->ctrl_token == HERE_DOC)
	{
		subtree->is_heredoc = TRUE;
		subtree->infile = get_nth_token_from_lst(tree, tree->tk_idx_set[1]);
		if (write_heredoc(subtree))
			return (EXIT_FAILURE);
	}
	if (tree->ctrl_token == D_RIGHT)
	{
		subtree->is_appending = TRUE;
		subtree->outfile = get_nth_token_from_lst(tree, tree->tk_idx_set[1]);
	}
	if (tree->ctrl_token == LEFT)
		subtree->infile = get_nth_token_from_lst(tree, tree->tk_idx_set[1]);
	if (tree->ctrl_token == RIGHT)
		subtree->outfile = get_nth_token_from_lst(tree, tree->tk_idx_set[1]);
	return (EXIT_SUCCESS);
}
