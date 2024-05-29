/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mallocs.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeshin <jeshin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 13:00:38 by seunghan          #+#    #+#             */
/*   Updated: 2024/05/29 12:49:32 by jeshin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_tree	*malloc_cmd_node(t_tree *now, t_list *tk_list, int cmd_cnt)
{
	int	i;

	i = 0;
	if (cmd_cnt > 0)
	{
		if (now && !now -> next_left)
			now = malloc_tree_node(now, tk_list, LEFT);
		else
			now = malloc_tree_node(now, tk_list, RIGHT);
		now -> ctrl_token = 0;
		now -> tk_idx_set = (int *)malloc(sizeof(int) * (cmd_cnt + 1));
		if (!now -> tk_idx_set)
			exit(1);
		while (i < cmd_cnt)
		{
			(now -> tk_idx_set)[i] = 0;
			i++;
		}
		(now -> tk_idx_set)[cmd_cnt] = END;
	}
	return (now);
}

static void	attach_node(t_tree *now, t_tree *next, int direct)
{
	if (now && direct == LEFT)
	{
		if (now -> next_left)
			now -> next_right = next;
		else
			now -> next_left = next;
		next -> prev = now;
	}
	else if (now && direct == RIGHT)
	{
		if (now -> next_right)
			now -> next_left = next;
		else
			now -> next_right = next;
		next -> prev = now;
	}
}

t_tree	*malloc_tree_node(t_tree *now, t_list *tk_list, int direct)
{
	static int	idx_s;
	t_tree		*next;

	if (!now)
		idx_s = 0;
	next = (t_tree *)malloc(sizeof(t_tree));
	if (!next)
		exit(1);
	next -> idx = idx_s;
	ini_tree_node(next, tk_list);
	attach_node(now, next, direct);
	idx_s++;
	return (next);
}
