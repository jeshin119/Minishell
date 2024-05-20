// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   test_errmsg.c                                      :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: jeshin <jeshin@student.42.fr>              +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2024/05/08 17:44:07 by jeshin            #+#    #+#             */
// /*   Updated: 2024/05/20 11:55:45 by jeshin           ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

// #include "../include/minishell.h"

// static int	syntax_err_msg(t_tree *tree, int i)
// {
// 	char	*msg;

// 	if (tree->tk_idx_set && tree->tk_idx_set[i])
// 	{
// 		msg = get_nth_token_from_lst(tree, tree->tk_idx_set[i]);
// 		ft_putstr_fd("bash: syntax error near unexpected token '", 2);
// 		ft_putstr_fd(msg, 2);
// 		ft_putstr_fd("'\n", 2);
// 		free(msg);
// 	}
// 	else
// 	{
// 		ft_putstr_fd("bash: syntax error near unexpected token '", 2);
// 		ft_putstr_fd("newline'\n", 2);
// 	}
// 	return (EXIT_FAILURE);
// }

// int	check_syntax_err(t_tree *tree)
// {
// 	int	putted;
// 	int	i;

// 	if (tree == 0)
// 		return (0);
// 	putted = 0;
// 	if (tree->next_left && tree->next_left->exit_code == 258)
// 	{
// 		putted += check_syntax_err(tree->next_left);
// 		if (putted)
// 			return (258);
// 	}
// 	if (tree->next_right && tree->next_right->exit_code == 258)
// 	{
// 		putted += check_syntax_err(tree->next_right);
// 		if (putted)
// 			return (258);
// 	}
// 	i = -1;
// 	while ((tree->tk_idx_set) && (tree->tk_idx_set)[++i] != -1)
// 		;
// 	i--;
// 	if (tree->tk_idx_set && tree->tk_idx_set[i])
// 		return (syntax_err_msg(tree, i));
// 	else
// 		return (syntax_err_msg(tree, i));
// 	return (EXIT_SUCCESS);
// }

// int	put_subtree_has_syntax_err_msg(t_tree *tree)
// {
// 	int	putted;

// 	if (tree == 0)
// 		return (0);
// 	putted = 0;
// 	if (tree->exit_code != 258)
// 	{
// 		putted += put_subtree_has_syntax_err_msg(tree->next_left);
// 		if (putted)
// 			return (258);
// 		putted += put_subtree_has_syntax_err_msg(tree->next_right);
// 		if (putted)
// 			return (258);
// 	}
// 	check_syntax_err(tree);
// 	return (EXIT_SUCCESS);
// }