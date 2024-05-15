/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   err.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeshin <jeshin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 17:44:07 by jeshin            #+#    #+#             */
/*   Updated: 2024/05/15 11:16:48 by jeshin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	put_errmsg_syntax_err(t_tree *tree)
{
	printf("here is put_errmsg in err.c\n");
	ft_putstr_fd("bash: syntax error near unexpected token ", 2);
	if (tree->tk_list->ctrl_token == PIPE)
		ft_putstr_fd("'|'\n", 2);
	else if (tree->tk_list -> prev && tree->tk_list -> prev -> ctrl_token)
	{
		ft_putstr_fd("'", 2);
		ft_putstr_fd(tree->tk_list->token, 2);
		ft_putstr_fd("'\n", 2);
	}
	else if (tree->tk_list -> next)
	{
		ft_putstr_fd("'", 2);
		ft_putstr_fd(tree->tk_list->next->token, 2);
		ft_putstr_fd("'\n", 2);
	}
	else
		ft_putstr_fd("'newline'\n", 2);
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

int	put_syntax_err_msg(char *s, int idx)
{
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
