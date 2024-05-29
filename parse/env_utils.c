/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeshin <jeshin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 12:04:47 by seunghan          #+#    #+#             */
/*   Updated: 2024/05/29 15:53:21 by seunghan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	env_first_ch_chk(char *s, int i)
{
	if (s[i])
	{
		if (s[i] < 'A' || (s[i] > 'Z' && s[i] < 'a') || s[i] > 'z')
		{
			if (s[i] != '_')
				return (0);
		}
	}
	return (1);
}

t_list	*mv_to_valid_token(t_tree *now, int i)
{
	t_list	*tk_list;

	tk_list = now -> tk_list;
	if (now -> tk_idx_set[i] == END)
		return (0);
	while (tk_list && tk_list -> token_idx != now -> tk_idx_set[i])
	{
		if (tk_list -> token_idx == now -> tk_idx_set[i])
			break ;
		tk_list = tk_list -> next;
	}
	return (tk_list);
}

int	name_valid_chk(char *name, char *s, int i)
{
	int	j;

	j = 0;
	while (name[j] && s[i])
	{
		if (name[j] != s[i])
			return (0);
		j++;
		i++;
	}
	if (name[j])
		return (0);
	return (1);
}

t_node	*env_name_chk(char *s, t_node *env_list, int i)
{
	int	valid;

	valid = 0;
	while (env_list)
	{
		valid = name_valid_chk(env_list -> name, s, i);
		if (valid)
			break ;
		env_list = env_list -> next;
	}
	if (!valid)
		return (0);
	return (env_list);
}

void	handle_qt(t_env *env_lset, int e_idx, int q_flag, int hd_flag)
{
	if (hd_flag)
		return ;
	if (q_flag == D_QUOTE)
		env_lset[e_idx]. d_quote = ON;
	else if (q_flag == S_QUOTE)
		env_lset[e_idx]. len = 0;
}
