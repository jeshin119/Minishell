/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mallocs.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seunghan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 13:00:38 by seunghan          #+#    #+#             */
/*   Updated: 2024/04/22 11:31:04 by seunghan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_tree	*malloc_cmd_node(t_tree *now, t_list *tk_list, int cmd_cnt)
{
	if (cmd_cnt > 0)
	{
		if (now && !now -> next_left)
			now = malloc_tree_node(now, tk_list, LEFT);
		else
			now = malloc_tree_node(now, tk_list, RIGHT);
		now -> tk_idx_set = (int *)malloc(sizeof(int) * (cmd_cnt + 1));
		if (!now -> tk_idx_set)
			exit(1);
		(now -> tk_idx_set)[cmd_cnt] = NONE;
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

static void	ini_tree_node(t_tree *next, t_list *tk_list)
{
	if (tk_list -> ctrl_token == PIPE)
		next -> pipe = 1;
	else
		next -> pipe = 0;
	next -> chked = OFF;
	next -> end_flag = OFF;
	next -> tk_idx_set = 0;
	next -> next_left = 0;
	next -> next_right = 0;
	next -> prev = 0;
}	

t_tree	*malloc_tree_node(t_tree *now, t_list *tk_list, int direct)
{
	static int	idx_s;
	t_tree		*next;

	next = (t_tree *)malloc(sizeof(t_tree));
	if (!next)
		exit(1);
	next -> idx = idx_s;
	ini_tree_node(next, tk_list);
	attach_node(now, next, direct);
	idx_s++;
	return (next);
}
