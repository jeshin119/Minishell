/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   err.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeshin <jeshin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 17:44:07 by jeshin            #+#    #+#             */
/*   Updated: 2024/05/29 15:06:21 by jeshin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	check_subtree_syntax_err(t_tree *tree, t_subtree **new)
{
	if ((tree && tree->exit_code == 258) && (new && *new))
	{
		put_subtree_has_syntax_err_msg(tree);
		free_subtree(new);
		g_status = 258;
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int	check_ambiguous(t_tree *tree, t_subtree *subtree)
{
	int		i;
	t_list	*start;

	if (tree == 0 || tree->tk_list == 0 || subtree == 0)
		return (EXIT_FAILURE);
	if (subtree->is_ambiguous)
		return (EXIT_SUCCESS);
	if (tree->tk_idx_set[1] == -1)
		return (EXIT_FAILURE);
	i = -1;
	start = tree->tk_list;
	while (start && ++i <= tree->tk_idx_set[1])
	{
		if (start->ambi_flag)
		{
			subtree->is_ambiguous = i;
			ft_putstr_fd("bash: ", 2);
			ft_putstr_fd(start->token, 2);
			ft_putstr_fd(": ambiguous redirect\n", 2);
			return (EXIT_SUCCESS);
		}
		start = start->next;
	}
	return (EXIT_SUCCESS);
}

int	is_subtree_ambiguous(t_subtree *subtree)
{
	if (subtree && subtree->is_ambiguous)
	{
		g_status = 1;
		return (TRUE);
	}
	return (FALSE);
}

int	has_subtree_no_infile(t_subtree *subtree)
{
	if (subtree && subtree->no_infile)
	{
		g_status = 1;
		return (TRUE);
	}
	return (FALSE);
}
