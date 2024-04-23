/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeshin <jeshin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 13:20:03 by seunghan          #+#    #+#             */
/*   Updated: 2024/04/24 11:22:43 by jeshin           ###   ########.fr       */
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

void	syntax_error_exit(t_list *tk_list)
{
	printf("syntax error near unexpected token ");
	if (tk_list -> ctrl_token == PIPE)
		printf("'|'\n");
	else if (tk_list -> prev && tk_list -> prev -> ctrl_token)
		printf("'%s'\n", tk_list -> token);
	else if (tk_list -> next)
		printf("'%s'\n", tk_list -> next -> token);
	else
		printf("'newline'\n");
	exit(1);
}

void	print_token_info(t_tree *now, int direct)
{
	char	*up;
	char	*left;
	char	*right;
	char	*out;
	char	*now_direct;

	up = "UP";
	left = "LEFT";
	right = "RIGHT";
	out = "OUT";
	if (direct == UPP)
		now_direct = up;
	if (direct == LEFT)
		now_direct = left;
	if (direct == RIGHT)
		now_direct = right;
	if (now -> end_flag)
		now_direct = out;
	if (now -> ctrl_token == PIPE)
	{
		printf("| -> %d  %s  end_flag = %d\n", now -> idx, now_direct, now -> end_flag);
		return ;
	}
	printf("-> %d  %s  end_flag = %d\n", now -> idx, now_direct, now -> end_flag);
}	

void	print_token(t_tree *now, t_list *tk_list, int direct)
{
	int		i;
	t_list	*head;

	i = 0;
	head = tk_list;
	if (now -> ctrl_token == PIPE)
	{
		print_token_info(now, direct);
		return ;
	}
	while ((now -> tk_idx_set)[i] >= 0)
	{
		tk_list = head;
		while (tk_list)
		{
			if (tk_list -> token_idx == (now -> tk_idx_set[i]))
				printf("%s  ", tk_list -> token);
			tk_list = tk_list -> next;
		}
		i++;
	}
	print_token_info(now, direct);
}

// void	preorder_travel(t_tree *now, t_list *tk_list) // tree안에 list포인터가있는데 매개변수로 또 받아야하는지?
// {
// 	while (!now -> end_flag) //끝일때까지 반복하는데 // 트리의 왼쪽과 오른쪽 없으면 0으로 초기화 되어있는지?
// 	{
// 		while (now -> next_left) //왼쪽으로 계속이동
// 		{						// 근디 애초에 pipe가 왼쪽에 한덩어리만 있는거 아닌가?
// 			print_token(now, tk_list, LEFT);
// 			now = now -> next_left;
// 		}
// 		while (now -> prev && !now -> pipe)
// 		{
// 			while (now -> next_right)  //오른쪽이 있으면? 루트의 왼쪽 첫번쨰 자식의 오른쪽 노드가 있나?
// 			{
// 				print_token(now, tk_list, RIGHT); // right가 뭐지?
// 				now = now -> next_right;
// 			}
// 			if (now -> end_flag)
// 				break ;
// 			print_token(now, tk_list, UPP);
// 			now = now -> prev;
// 		}
// 		if (now -> end_flag)
// 			break ;
// 		print_token(now, tk_list, RIGHT);
// 		if (now -> next_right)
// 			now = now -> next_right;
// 	}
// 	print_token(now, tk_list, 0);
// }

// void preOrder(int here){ 
// 	if (visited[here]) 
// 		return ;
// 	visited[here]=true;
// 	if (adj[here].size() == 1)
// 		postOrder(adj[here][0]);
// 	if (adj[here].size() == 2){
// 		postOrder(adj[here][0]);
// 		postOrder(adj[here][1]);
// 	}
// }  