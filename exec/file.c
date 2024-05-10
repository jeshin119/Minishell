/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeshin <jeshin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 18:11:23 by jeshin            #+#    #+#             */
/*   Updated: 2024/05/10 17:14:50 by jeshin           ###   ########.fr       */
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
		return (open(subtree->infile, O_RDONLY));
	if (subtree->is_heredoc == OFF && subtree->infile != NULL)
	{
		return (open_infile_n_return(subtree));
	}
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

// static int	more_than_oneelem(char *file)
// {
// 	if (file == 0 || *file == 0)
// 		return (FALSE);
// 	while (*file)
// 	{
// 		if (ft_isspace(*file))
// 			return (TRUE);
// 	}
// 	return (FALSE);
// }

int	get_infile(t_tree *tree, t_subtree *new, t_dq *env)
{
	if (tree == 0)
		return (EXIT_SUCCESS);
	if (tree->next_left && (tree->next_left)->ctrl_token != 0)
		return (get_infile(tree->next_left, new, env));
	if (tree->exit_code == 258)
	{
		put_errmsg_syntax_err(tree);
		return (EXIT_FAILURE);
	}
	if (tree->ctrl_token == HERE_DOC)
	{
		new->is_heredoc = TRUE;
		new->infile = get_nth_token_from_lst(tree, tree->tk_idx_set[1]);
		if (write_heredoc(new))
			return (EXIT_FAILURE);
	}
	if (tree->ctrl_token == LEFT)
	{
		env_chk(tree, env->head);
		new->infile = get_nth_token_from_lst(tree, tree->tk_idx_set[1]);
	}
	return (EXIT_SUCCESS);
}

int	get_outfile(t_tree *tree, t_subtree *new, t_dq *env)
{
	if (tree == 0)
		return (EXIT_SUCCESS);
	if (tree->next_right && (tree->next_right)->ctrl_token != 0)
		return (get_outfile(tree->next_right, new, env));
	if (tree->exit_code == 258)
	{
		put_errmsg_syntax_err(tree);
		return (EXIT_FAILURE);
	}
	if (tree->ctrl_token != D_RIGHT && tree->ctrl_token != RIGHT)
		return (EXIT_SUCCESS);
	if (tree->ctrl_token == D_RIGHT)
		new->is_appending = 1;
	env_chk(tree, env->head);
	new->outfile = get_nth_token_from_lst(tree, tree->tk_idx_set[1]);
	if (new->outfile == NULL)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
