/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   err.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeshin <jeshin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 17:44:07 by jeshin            #+#    #+#             */
/*   Updated: 2024/05/17 17:47:49 by jeshin           ###   ########.fr       */
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
