/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   err.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeshin <jeshin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 17:44:07 by jeshin            #+#    #+#             */
/*   Updated: 2024/05/13 11:47:21 by jeshin           ###   ########.fr       */
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
