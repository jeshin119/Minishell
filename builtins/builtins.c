/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeshin <jeshin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 11:07:19 by jeshin            #+#    #+#             */
/*   Updated: 2024/05/14 16:07:49 by jeshin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	go_builtin(t_subtree *subtree, t_dq *env)
{
	if (subtree->cmd == 0)
		return (EXIT_FAILURE);
	if (!ft_strncmp(subtree->cmd, "echo", 5))
		return (_echo(subtree));
	else if (!ft_strncmp(subtree->cmd, "cd", 3))
		return (_cd(subtree->opt[1], env));
	else if (!ft_strncmp(subtree->cmd, "pwd", 4))
		return (_pwd());
	else if (!ft_strncmp(subtree->cmd, "export", 7))
		return (_export(subtree->opt, env));
	else if (!ft_strncmp(subtree->cmd, "unset", 6))
		return (_unset(subtree->opt, env));
	else if (!ft_strncmp(subtree->cmd, "env", 4))
		return (_env(env));
	else if (!ft_strncmp(subtree->cmd, "exit", 5))
	{
		if (subtree->next == 0 && subtree->prev == 0)
			return (_bexit_(subtree->opt, env));
		else
			return (_exit_(subtree->opt));
	}
	return (EXIT_FAILURE);
}

int	is_builtin(t_subtree *subtree)
{
	if (subtree->cmd == 0)
		return (FALSE);
	if (!ft_strncmp(subtree->cmd, "echo", 5))
		return (TRUE);
	else if (!ft_strncmp(subtree->cmd, "cd", 3))
		return (TRUE);
	else if (!ft_strncmp(subtree->cmd, "pwd", 4))
		return (TRUE);
	else if (!ft_strncmp(subtree->cmd, "export", 7))
		return (TRUE);
	else if (!ft_strncmp(subtree->cmd, "unset", 6))
		return (TRUE);
	else if (!ft_strncmp(subtree->cmd, "env", 4))
		return (TRUE);
	else if (!ft_strncmp(subtree->cmd, "exit", 5))
		return (TRUE);
	else
		return (FALSE);
	return (TRUE);
}
