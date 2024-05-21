/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subtree_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeshin <jeshin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 18:11:23 by jeshin            #+#    #+#             */
/*   Updated: 2024/05/21 13:08:57 by jeshin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	get_cmd_opt(t_tree *tree, t_subtree **new, t_dq *env)
{
	if (tree == 0)
		return (EXIT_SUCCESS);
	if (check_subtree_syntax_err(tree, new))
		return (EXIT_FAILURE);
	if (tree->ctrl_token != 0)
		return (get_cmd_opt(tree->next_left, new, env));
	env_chk(tree, env->head);
	(*new)->cmd = get_nth_token_from_lst(tree, (tree->tk_idx_set)[0]);
	if (tree->tk_idx_set[0] == -1)
		(*new)->is_ambiguous = 1;
	get_opt_from_lst(tree, new);
	return (EXIT_SUCCESS);
}

static int	check_file_is(t_tree *tree, t_subtree **new)
{
	char		*file;
	struct stat	statbuf;

	if (tree->ctrl_token != LEFT && tree->ctrl_token != RIGHT)
		return (EXIT_SUCCESS);
	file = get_nth_token_from_lst(tree, tree->tk_idx_set[1]);
	stat(file, &statbuf);
	if (S_ISREG(statbuf.st_mode) == 0)
	{
		(*new)->no_infile = file;
		return (EXIT_FAILURE);
	}
	free(file);
	return (EXIT_SUCCESS);
}

int	get_infile(t_tree *tree, t_subtree **new, t_dq *env)
{
	if (tree == 0)
		return (EXIT_SUCCESS);
	if (check_subtree_syntax_err(tree, new))
		return (free_subtree(new));
	if (tree->ctrl_token == HERE_DOC)
	{
		check_already_has_heredoc(*new);
		if (get_heredoc(tree, *new, env))
			return (EXIT_FAILURE);
	}
	if (tree->ctrl_token == LEFT && (*new)->no_infile == NULL)
		check_file_is(tree, new);
	if (tree->next_left && (tree->next_left)->ctrl_token != 0)
		return (get_infile(tree->next_left, new, env));
	if (tree->ctrl_token == LEFT)
	{
		check_already_has_heredoc(*new);
		env_chk(tree, env->head);
		if (tree->tk_idx_set[1] == -1)
			(*new)->is_ambiguous = 1;
		(*new)->infile = get_nth_token_from_lst(tree, tree->tk_idx_set[1]);
	}
	return (EXIT_SUCCESS);
}

int	get_outfile(t_tree *tree, t_subtree **new, t_dq *env)
{
	if (tree == 0)
		return (EXIT_SUCCESS);
	if (check_subtree_syntax_err(tree, new))
		return (free_subtree(new));
	if (tree->next_right && (tree->next_right)->ctrl_token != 0)
		return (get_outfile(tree->next_right, new, env));
	if (tree->ctrl_token != D_RIGHT && tree->ctrl_token != RIGHT)
		return (EXIT_SUCCESS);
	if (tree->ctrl_token == D_RIGHT)
		(*new)->is_appending = 1;
	env_chk(tree, env->head);
	if (tree->tk_idx_set[1] == -1)
		(*new)->is_ambiguous = 1;
	(*new)->outfile = get_nth_token_from_lst(tree, tree->tk_idx_set[1]);
	return (EXIT_SUCCESS);
}
