/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   err.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeshin <jeshin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 17:44:07 by jeshin            #+#    #+#             */
/*   Updated: 2024/05/16 11:02:48 by jeshin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	syntax_err_msg(t_tree *tree, int i)
{
	char	*msg;

	if (tree->tk_idx_set[i])
	{
		msg = get_nth_token_from_lst(tree, tree->tk_idx_set[i]);
		ft_putstr_fd("bash: syntax error near unexpected token '", 2);
		ft_putstr_fd(msg, 2);
		ft_putstr_fd("'\n", 2);
		free(msg);
	}
	else
	{
		ft_putstr_fd("bash: syntax error near unexpected token '", 2);
		ft_putstr_fd("newline'\n", 2);
	}
	return (EXIT_FAILURE);
}

int	put_errmsg_syntax_err(t_tree *tree)
{
	int	putted;
	int	i;

	if (tree == 0)
		return (0);
	putted = 0;
	if (tree->exit_code != 258)
	{
		putted += put_errmsg_syntax_err(tree->next_left);
		if (putted)
			return (EXIT_FAILURE);
		putted += put_errmsg_syntax_err(tree->next_right);
		if (putted)
			return (EXIT_FAILURE);
	}
	i = -1;
	while ((tree->tk_idx_set)[++i] != -1)
		;
	i--;
	if (tree->tk_idx_set[i])
		return (syntax_err_msg(tree, i));
	else
		return (syntax_err_msg(tree, i));
	return (EXIT_SUCCESS);
}

int	is_file_err(t_tree *tree, t_subtree *new, t_dq *env, int ret)
{
	if (ret == 258)
	{
		put_errmsg_syntax_err(tree);
		free_subtree(new);
		g_status = 258;
		update_prev_status(env);
		return (EXIT_FAILURE);
	}
	if (ret == EXIT_FAILURE)
	{
		free_subtree(new);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int	put_syntax_err_msg(char *s, int idx, int heredoc)
{
	if (heredoc)
		return (EXIT_SUCCESS);
	ft_putstr_fd("bash: syntax error near unexpected token `", 2);
	if (s[idx])
		write(2, &s[idx], 1);
	else
		write(2, "newline", 7);
	ft_putstr_fd("'\n", 2);
	free(s);
	g_status = 258;
	return (EXIT_FAILURE);
}

int	put_command_not_found(char *cmd)
{
	ft_putstr_fd("bash: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": command not found\n", 2);
	exit(127);
	return (EXIT_FAILURE);
}
