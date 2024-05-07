/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_tree.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeshin <jeshin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 18:17:41 by seunghan          #+#    #+#             */
/*   Updated: 2024/05/08 11:46:15 by jeshin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_tree	*reassembly(t_tree *now, t_list *tk_list)
{
	now = make_pipe_node(now, tk_list);
	now = make_rd_node(now, tk_list, LEFT);
	now = make_cmd_node(now, tk_list);
	if (right_rd_chk(tk_list))
		now = go_to_subroot(now);
	now = make_rd_node(now, tk_list, RIGHT);
	if (pipe_chk(tk_list))
		now = go_to_pipe(now);
	return (now);
}

t_tree	*make_tree(t_tree *now, t_list *tk_list)
{
	while (tk_list)
	{
		if (!tk_list -> prev || tk_list -> prev -> ctrl_token == PIPE)
			now = reassembly(now, tk_list);
		tk_list = tk_list -> next;
	}
	now -> end_flag = ON;
	while (now -> prev)
		now = now -> prev;
	return (now);
}
