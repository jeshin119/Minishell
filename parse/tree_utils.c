/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeshin <jeshin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 13:20:03 by seunghan          #+#    #+#             */
/*   Updated: 2024/05/07 17:59:09 by jeshin           ###   ########.fr       */
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

void	syntax_error_exit(t_tree *now, t_list *tk_list)
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
	now -> exit_code = 258;
}

void	print_env_lset(t_tree *now)
{
	int	i;

	i = 0;
	while ((now -> tk_list -> env_lset)[i]. len != END)
	{
		printf("%d  ", (now -> tk_list -> env_lset)[i]. len);
		i++;
	}
	printf("\n");
}

void	print_token_info(t_tree *now, int direct)
{
	char	*up;
	char	*left;
	char	*right;
	char	*out;
	char	*now_direct;
	int		i;

	i = 0;
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
	//print_env_lset(now);
}	

void	print_token(t_tree *now, t_list *tk_list, int direct, t_node *env_list)
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
	env_chk(now, env_list);
	if (now -> ambi_flag)
		return ;
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

void	preorder_travel(t_tree *now, t_list *tk_list, t_node *env_list)
{
	while (!now -> end_flag)
	{
		now -> chked = ON;
		while (now -> next_left && !now -> next_left -> chked)
		{
			print_token(now, tk_list, LEFT, env_list);
			now -> chked = ON;
			now = now -> next_left;
		}
		now -> chked = ON;
		while (now -> prev && now -> ctrl_token != PIPE)
		{
			while (now -> next_right && !now -> next_right -> chked)
			{
				print_token(now, tk_list, RIGHT, env_list);
				now -> chked = ON;
				now = now -> next_right;
			}
			now -> chked = ON;
			if (now -> end_flag)
				break ;
			print_token(now, tk_list, UPP, env_list);
			now = now -> prev;
		}
		if (now -> end_flag)
			break ;
		print_token(now, tk_list, RIGHT, env_list);
		if (now -> next_right)
			now = now -> next_right;
	}
	print_token(now, tk_list, 0, env_list);
}
