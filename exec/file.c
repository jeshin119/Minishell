/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeshin <jeshin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 18:11:23 by jeshin            #+#    #+#             */
/*   Updated: 2024/05/16 21:12:18 by jeshin           ###   ########.fr       */
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

int	check_file_is(t_tree *tree, t_subtree **new)
{
	char	*file;
	struct	stat statbuf;

	if (tree->ctrl_token != LEFT && tree->ctrl_token != RIGHT)
		return (EXIT_SUCCESS);
	file = get_nth_token_from_lst(tree, tree->tk_idx_set[1]);
	stat(file, &statbuf);
	if (S_ISREG(statbuf.st_mode) == 0)
	{
		g_status = ENOENT;
		(*new)->no_infile = file;
		return (EXIT_FAILURE);
	}
	free(file);
	return (EXIT_SUCCESS);
}

int	get_infile(t_tree *tree, t_subtree *new, t_dq *env)
{
	if (tree == 0)
		return (EXIT_SUCCESS);
	if (tree->exit_code == 258)
		return (258);
	if (tree->ctrl_token == HERE_DOC && get_heredoc(tree, new))
		return (EXIT_FAILURE);
	if (tree->ctrl_token == LEFT && new->no_infile == 0)
		check_file_is(tree, &new);
	if (tree->next_left && (tree->next_left)->ctrl_token != 0)
		return (get_infile(tree->next_left, new, env));
	if (tree->ctrl_token == LEFT)
	{
		new->is_heredoc = 0;
		env_chk(tree, env->head);
		if (tree->tk_idx_set[1] == -1)
			new->is_ambiguous = 1;
		new->infile = get_nth_token_from_lst(tree, tree->tk_idx_set[1]);
	}
	return (EXIT_SUCCESS);
}

int	get_outfile(t_tree *tree, t_subtree *new, t_dq *env)
{
	if (tree == 0)
		return (EXIT_SUCCESS);
	if (tree->exit_code == 258)
		return (258);
	if (tree->next_right && (tree->next_right)->ctrl_token != 0)
		return (get_outfile(tree->next_right, new, env));
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
