/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initilize.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seunghan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 17:38:54 by seunghan          #+#    #+#             */
/*   Updated: 2024/05/28 17:40:09 by seunghan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ini_q_flag_idx(int *q_flag, int *i)
{
	*q_flag = 0;
	*i = 0;
}

t_env	*ini_env_lset(t_env *env_lset, int env_cnt)
{
	int	i;

	i = 0;
	while (i < env_cnt)
	{
		env_lset[i]. len = 0;
		env_lset[i]. d_quote = 0;
		env_lset[i]. white_flag = 0;
		i++;
	}
	return (env_lset);
}

void	ini_tree_node(t_tree *next, t_list *tk_list_arg)
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
