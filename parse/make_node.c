/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_node.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeshin <jeshin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 13:20:03 by seunghan          #+#    #+#             */
/*   Updated: 2024/05/29 12:49:25 by jeshin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_tree	*make_pipe_node(t_tree *now, t_list *tk_list)
{
	while (tk_list -> next)
	{
		if (tk_list -> ctrl_token == PIPE)
			break ;
		tk_list = tk_list -> next;
	}
	if (tk_list -> ctrl_token != PIPE)
		return (now);
	if (tk_list -> prev && tk_list -> prev -> ctrl_token != PIPE)
	{
		if (!now)
			now = malloc_tree_node(now, tk_list, NO_DR);
		else
			now = malloc_tree_node(now, tk_list, RIGHT);
	}
	else
		now = syntax_error_malloc(now, tk_list, PIPE);
	return (now);
}

t_tree	*make_rd_node(t_tree *now, t_list *tk_list, int direct)
{
	int	db_drt;

	db_drt = get_double_direct(direct);
	while (tk_list && tk_list -> ctrl_token != PIPE)
	{
		if (tk_list -> ctrl_token == db_drt || tk_list -> ctrl_token == direct)
		{
			now = malloc_tree_node(now, tk_list, direct);
			now -> tk_idx_set = (int *)malloc(sizeof(int) * (2 + 1));
			if (!now -> tk_idx_set)
				exit(1);
			(now -> tk_idx_set)[2] = END;
			(now -> tk_idx_set)[0] = tk_list -> token_idx;
			if (tk_list -> next && !tk_list -> next -> ctrl_token)
				(now -> tk_idx_set)[1] = tk_list -> next -> token_idx;
			else
				now = syntax_error_malloc(now, tk_list, direct);
		}
		tk_list = tk_list -> next;
	}
	return (now);
}

int	get_cmd_cnt(t_list *tk_list)
{
	int	cmd_cnt;

	cmd_cnt = 0;
	while (tk_list && tk_list -> ctrl_token != PIPE)
	{
		if (!tk_list -> ctrl_token)
			cmd_cnt++;
		if (tk_list -> ctrl_token && tk_list -> next)
			cmd_cnt--;
		tk_list = tk_list -> next;
	}
	return (cmd_cnt);
}

static t_list	*move_rd_filename(t_list *tk_list)
{
	if (tk_list -> prev && tk_list -> prev -> ctrl_token)
	{
		if (tk_list -> prev -> ctrl_token != PIPE)
			tk_list = tk_list -> next;
		if (!tk_list)
			return (tk_list);
	}
	return (tk_list);
}

t_tree	*make_cmd_node(t_tree *now, t_list *tk_list)
{
	int	i;

	i = 0;
	now = malloc_cmd_node(now, tk_list, get_cmd_cnt(tk_list));
	if (now && now -> ctrl_token == PIPE)
		return (now);
	while (tk_list && tk_list -> ctrl_token != PIPE)
	{
		if (!tk_list -> ctrl_token)
		{
			tk_list = move_rd_filename(tk_list);
			if (!tk_list)
				return (now);
			if (!tk_list -> ctrl_token && (now -> tk_idx_set[i] >= 0))
			{
				(now -> tk_idx_set)[i] = tk_list -> token_idx;
				i++;
			}
		}
		tk_list = tk_list -> next;
	}
	return (now);
}
