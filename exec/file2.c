// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   file2.c                                            :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: jeshin <jeshin@student.42.fr>              +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2024/05/08 18:11:23 by jeshin            #+#    #+#             */
// /*   Updated: 2024/05/16 13:25:37 by jeshin           ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

// #include "../include/minishell.h"


// int	get_infile2(t_tree *tree, t_subtree *new, t_dq *env)
// {
// 	if (tree == 0)
// 		return (EXIT_SUCCESS);
// 	if (tree->exit_code == 258)
// 		return (258);
// 	if (tree->ctrl_token == HERE_DOC)
// 	{
// 		new->infile = get_nth_token_from_lst(tree, tree->tk_idx_set[1]);
// 		if (get_heredoc(new, env))
// 			return (EXIT_FAILURE);
// 	}
// 	if (tree->next_left && (tree->next_left)->ctrl_token != 0)
// 	{
// 		check_file_is(tree, new, 0);
// 		return (get_infile(tree->next_left, new, env));
// 	}
// 	if (tree->ctrl_token == LEFT)
// 	{
// 		new->is_heredoc = 0;
// 		env_chk(tree, env->head);
// 		new->infile = get_nth_token_from_lst(tree, tree->tk_idx_set[1]);
// 	}
// 	return (EXIT_SUCCESS);
// }

// int	get_infile(t_tree *tree, t_subtree *new, t_dq *env)
// {
// 	if (tree == 0)
// 		return (EXIT_SUCCESS);
// 	if (tree->exit_code == 258)
// 		return (258);
// 	if (tree->ctrl_token == HERE_DOC)
// 	{
// 		if (get_heredoc(tree, new, env))
// 			return (EXIT_FAILURE);
// 	}
// 	if (tree->next_left && (tree->next_left)->ctrl_token != 0)
// 		return (get_infile(tree->next_left, new, env));
// 	if (tree->ctrl_token == LEFT)
// 	{
// 		new->is_heredoc = 0;
// 		env_chk(tree, env->head);
// 		new->infile = get_nth_token_from_lst(tree, tree->tk_idx_set[1]);
// 	}
// 	return (EXIT_SUCCESS);
// }

// int	get_outfile(t_tree *tree, t_subtree *new, t_dq *env)
// {
// 	if (tree == 0)
// 		return (EXIT_SUCCESS);
// 	if (tree->exit_code == 258)
// 		return (258);
// 	if (tree->next_right && (tree->next_right)->ctrl_token != 0)
// 		return (get_outfile(tree->next_right, new, env));
// 	if (tree->ctrl_token != D_RIGHT && tree->ctrl_token != RIGHT)
// 		return (EXIT_SUCCESS);
// 	if (tree->ctrl_token == D_RIGHT)
// 		new->is_appending = 1;
// 	env_chk(tree, env->head);
// 	new->outfile = get_nth_token_from_lst(tree, tree->tk_idx_set[1]);
// 	if (new->outfile == NULL)
// 		return (EXIT_FAILURE);
// 	return (EXIT_SUCCESS);
// }
