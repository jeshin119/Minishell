/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_len_chk.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeshin <jeshin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 18:22:02 by seunghan          #+#    #+#             */
/*   Updated: 2024/05/22 12:32:40 by jeshin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	env_count_chk(char *s)
{
	int	i;
	int	env_cnt;

	i = 0;
	env_cnt = 0;
	while (s[i])
	{
		if (s[i] == '$')
		{
			if (s[i + 1] && s[i + 1] != '\\')
			{
				if (white_chk(s[i + 1]) && s[i + 1] != '$')
					env_cnt++;
			}
		}
		i++;
	}
	return (env_cnt);
}

int	env_name_len_chk(char *s, int *i)
{
	int	name_len;
	int	j;

	j = *i;
	name_len = 0;
	if (!env_first_ch_chk(s, *i))
		return (name_len);
	while (s[j])
	{
		if ((s[j] >= 'A' && s[j] <= 'Z') || (s[j] >= 'a' && s[j] <= 'z'))
		{
			name_len++;
			(*i)++;
		}
		else if ((s[j] >= '0' && s[j] <= '9') || s[j] == '_')
		{
			name_len++;
			(*i)++;
		}
		else
			break ;
		j++;
	}
	return (name_len);
}

void	get_env_len(char *s, int *i, int e_idx, t_env *env_lset)
{
	int	env_len;

	env_len = 0;
	env_len = env_name_len_chk(s, i);
	if (s[(*i)] == '?' || (s[(*i)] >= '0' && s[(*i)] <= '9'))
		env_len = 1;
	env_lset[e_idx]. len = env_len;
}

static int	is_quote(char *s, int i, int q_flag)
{
	if (q_flag == D_QUOTE)
	{
		if (s[i - 1] != '\\' && s[i] == '\"')
			return (1);
	}
	else if (q_flag == S_QUOTE)
	{
		if (s[i - 1] != '\\' && s[i] == '\'')
			return (1);
	}
	return (0);
}

void	alloc_env_len(t_env *env_lset, char *s, int e_idx, int hd_flag)
{
	int	q_flag;
	int	i;

	ini_q_flag_idx(&q_flag, &i);
	while (s[i])
	{
		if (q_flag >= QUOTES && is_quote(s, i, q_flag))
			q_flag = 0;
		else if (q_flag < QUOTES)
			q_flag = meta_chk(s, i, q_flag);
		if (s[i] == '$' && s[i + 1])
		{
			i++;
			if (s[i] && s[i] != '\\' && white_chk(s[i]) && s[i] != '$')
			{
				get_env_len(s, &i, e_idx, env_lset);
				handle_qt(env_lset, e_idx, q_flag, hd_flag);
				e_idx++;
			}
			if (s[i] == '$' || is_quote(s, i, q_flag))
				i--;
		}
		if (s[i])
			i++;
	}
}
