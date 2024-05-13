/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   err.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeshin <jeshin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 17:44:07 by jeshin            #+#    #+#             */
/*   Updated: 2024/05/13 18:32:34 by jeshin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	put_errmsg_syntax_err(t_tree *tree)
{
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

void	put_errmsg_syntax_err2(t_tree *tree)
{
	ft_putstr_fd("bash: syntax error near unexpected token ", 2);
	if (tree)
	{
		ft_putstr_fd("'|'\n", 2);

		ft_putstr_fd("'", 2);
		ft_putstr_fd(tree->tk_list->token, 2);
		ft_putstr_fd("'\n", 2);

		ft_putstr_fd("'", 2);
		ft_putstr_fd(tree->tk_list->next->token, 2);
		ft_putstr_fd("'\n", 2);

		ft_putstr_fd("'newline'\n", 2);
	}
}

int	is_file_err(t_tree *tree, t_subtree *new, int ret)
{
	if (ret == 258)
	{
		put_errmsg_syntax_err(tree);
		free_subtree(new);
		update_prev_status(258);
		return (EXIT_FAILURE);
	}
	if (ret == EXIT_FAILURE)
	{
		free_subtree(new);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
