/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeshin <jeshin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 13:20:03 by seunghan          #+#    #+#             */
/*   Updated: 2024/05/09 17:53:09 by jeshin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_tree	*go_to_pipe(t_tree *now)
{
	if (!now)
		return (0);
	while (now -> prev)
	{
		if (now -> ctrl_token == PIPE)
			return (now);
		now = now -> prev;
	}
	return (now);
}

t_tree	*go_to_subroot(t_tree *now)
{
	if (!now)
		return (0);
	while (now -> prev)
	{
		if (now -> prev -> ctrl_token == PIPE)
			return (now);
		now = now -> prev;
	}
	return (now);
}

t_tree	*syntax_error_malloc(t_tree *now, t_list *tk_list, int meta_value)
{
	if (meta_value == PIPE)
	{
		if (!now)
			now = malloc_tree_node(now, tk_list, NO_DR);
		else
			now = malloc_tree_node(now, tk_list, RIGHT);
	}
	else if (meta_value >= LEFT && meta_value <= D_RIGHT)
	{
		if (tk_list -> next)
			(now -> tk_idx_set)[1] = tk_list -> next -> token_idx;
	}
	now -> exit_code = 258;
	return (now);
}
