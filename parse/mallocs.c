/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mallocs.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeshin <jeshin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 13:00:38 by seunghan          #+#    #+#             */
/*   Updated: 2024/05/07 17:58:23 by jeshin           ###   ########.fr       */
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

t_env	*ini_env_lset(t_env *env_lset, int env_cnt)
{
	int	i;

	i = 0;
	while (i < env_cnt)
	{
		env_lset[i]. len = 0;
		env_lset[i]. d_quote = 0;
		i++;
	}
	return (env_lset);
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

static void	ini_tree_node(t_tree *next, t_list *tk_list_arg)
{
	if (tk_list_arg -> ctrl_token)
		next -> ctrl_token = tk_list_arg -> ctrl_token;
	else
		next -> ctrl_token = 0;
	while (tk_list_arg -> prev)
		tk_list_arg = tk_list_arg -> prev;
	next -> tk_list = tk_list_arg;
	next -> chked = OFF;
	next -> end_flag = OFF;
	next -> ambi_flag = OFF;
	next -> exit_code = 0;
	next -> tk_idx_set = 0;
	next -> next_left = 0;
	next -> next_right = 0;
	next -> prev = 0;
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
