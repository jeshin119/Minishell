/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   err.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeshin <jeshin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 17:44:07 by jeshin            #+#    #+#             */
/*   Updated: 2024/05/15 15:00:01 by jeshin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	put_errmsg_syntax_err(t_tree *tree)
{
	int putted;

	if (tree == 0)
		return (0);
	putted = 0;
	if (tree->exit_code != 258)
	{
		putted += put_errmsg_syntax_err(tree->next_left);
		if (putted)
			return (1);
		putted += put_errmsg_syntax_err(tree->next_right);
		if (putted)
			return (1);
	}
	printf("here is put_errmsg in err.c\n");
	int i=-1;
	while((tree->tk_idx_set)[++i] != -1)
		;
	i--;
	if (tree->tk_idx_set[i])
	{
		char *tmp = get_nth_token_from_lst(tree, tree->tk_idx_set[i]);
		ft_putstr_fd("bash: syntax error near unexpected token '", 2);
		ft_putstr_fd(tmp, 2);
		ft_putstr_fd("'\n", 2);
		free(tmp);
		return (1);
	}
	else
	{
		ft_putstr_fd("bash: syntax error near unexpected token '", 2);
		ft_putstr_fd("newline'\n", 2);
		return (1);
	}
	return (0);
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

int	is_directory(char *path)
{
	struct stat	statbuf;

	stat(path, &statbuf);
	if (S_ISDIR(statbuf.st_mode))
	{
		ft_putstr_fd(path, 2);
		ft_putstr_fd(": is a directory\n", 2);
		return (TRUE);
	}
	else
		return (FALSE);
}
