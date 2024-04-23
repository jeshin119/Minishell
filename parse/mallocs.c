/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mallocs.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeshin <jeshin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 13:00:38 by seunghan          #+#    #+#             */
/*   Updated: 2024/04/23 12:31:32 by seunghan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

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
		else if (!now -> next_left && !now -> next_right) // 양쪽 모두에 자식이 없을때 왼쪽으로 붙히기
			now -> next_left = next;
		else
			now -> next_right = next;
		next -> prev = now;
	}
}

static void	ini_tree_node(t_tree *next, t_list *tk_list_arg) // tk_list_arg = 매개변수로 들어온 토큰 리스트
{
	if (tk_list_arg -> ctrl_token)
		next -> ctrl_token = tk_list_arg -> ctrl_token; // 토큰 리스트에서 트리 노드로 컨트롤 토큰 정보 복사
	else
		next -> ctrl_token = 0;
	while (tk_list_arg -> prev) // 토큰 리스트 0번째로 이동
		tk_list_arg = tk_list_arg -> prev;
	next -> tk_list = tk_list_arg; // next -> tk_list = 트리 노드 멤버변수(토큰 리스트 포인터)에 0번째 토큰리스트 주소 대입
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
