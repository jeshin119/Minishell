/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errmsg.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeshin <jeshin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 17:44:07 by jeshin            #+#    #+#             */
/*   Updated: 2024/05/29 17:05:25 by jeshin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	syntax_err_msg(t_tree *tree, int i)
{
	char	*msg;

	if (tree->ctrl_token == PIPE)
		ft_putstr_fd("bash: syntax error near unexpected token '|'\n", 2);
	else if (tree->tk_idx_set && tree->tk_idx_set[i + 1] == -1)
	{
		ft_putstr_fd("bash: syntax error near unexpected token '", 2);
		ft_putstr_fd("newline'\n", 2);
	}
	else if (tree->tk_idx_set && tree->tk_idx_set[i])
	{
		msg = get_nth_token_from_lst(tree, tree->tk_idx_set[i]);
		ft_putstr_fd("bash: syntax error near unexpected token '", 2);
		ft_putstr_fd(msg, 2);
		ft_putstr_fd("'\n", 2);
		free(msg);
	}
	return (EXIT_FAILURE);
}

int	put_subtree_has_syntax_err_msg(t_tree *tree)
{
	int	putted;
	int	i;

	if (tree == 0)
		return (0);
	putted = 0;
	if (tree->exit_code != 258)
	{
		putted += put_subtree_has_syntax_err_msg(tree->next_left);
		if (putted)
			return (258);
		putted += put_subtree_has_syntax_err_msg(tree->next_right);
		if (putted)
			return (258);
	}
	if (tree->ctrl_token == PIPE)
		return (syntax_err_msg(tree, 0));
	i = -1;
	while ((tree->tk_idx_set) && (tree->tk_idx_set)[++i] != -1)
		;
	i--;
	return (syntax_err_msg(tree, i));
}

int	put_subtree_has_nofile_err_msg(t_subtree *subtree)
{
	ft_putstr_fd("bash: ", 2);
	ft_putstr_fd(subtree->no_infile, 2);
	ft_putstr_fd(": No such file or directory\n", 2);
	free(subtree->no_infile);
	subtree->no_infile = 0;
	g_status = 1;
	return (EXIT_FAILURE);
}

int	put_buf_has_syntax_err_msg(char *s, int idx, int heredoc)
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
