/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seunghan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 13:20:03 by seunghan          #+#    #+#             */
/*   Updated: 2024/04/22 12:32:20 by seunghan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_tree	*go_to_pipe(t_tree *now)
{
	if (!now)
		return (0);
	while (now -> prev)
	{
		if (now -> pipe)
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
		if (now -> prev -> pipe)
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
	if (now -> pipe)
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
	if (now -> pipe)
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

void	preorder_travel(t_tree *now, t_list *tk_list)
{
	while (!now -> end_flag)
	{
		while (now -> next_left)
		{
			print_token(now, tk_list, LEFT);
			now = now -> next_left;
		}
		while (now -> prev && !now -> pipe)
		{
			while (now -> next_right)
			{
				print_token(now, tk_list, RIGHT);
				now = now -> next_right;
			}
			if (now -> end_flag)
				break ;
			print_token(now, tk_list, UPP);
			now = now -> prev;
		}
		if (now -> end_flag)
			break ;
		print_token(now, tk_list, RIGHT);
		if (now -> next_right)
			now = now -> next_right;
	}
	print_token(now, tk_list, 0);
}
