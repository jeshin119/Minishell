/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_tokenize.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seunghan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 18:22:02 by seunghan          #+#    #+#             */
/*   Updated: 2024/05/02 17:17:54 by seunghan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	env_count_chk(char *s, t_list *tk_list)
{
	int	i;
	int	env_cnt;

	i = 0;
	env_cnt = 0;
	while (tk_list -> env_lset && tk_list -> env_lset[env_cnt]. len != END)
		env_cnt++;
	while (s[i])
	{
		if (s[i] == '$')
		{
			if (s[i + 1] && s[i + 1] != '\\')
			{
				if (s[i + 1] != ' ' && s[i + 1] != '$')
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

static int	cpy_former_env_lset(t_env *env_lset_new, t_list *tk_list, int e_idx)
{
	while ((tk_list -> env_lset)[e_idx]. len != END)
	{
		env_lset_new[e_idx]. len = (tk_list -> env_lset)[e_idx]. len;
		env_lset_new[e_idx]. d_quote = (tk_list -> env_lset)[e_idx]. d_quote;
		e_idx++;
	}
	return (e_idx);
}

static void	alloc_env_len(t_env *env_lset_new, char *s, int e_idx, int m_t)
{
	int	env_len;
	int	i;

	i = 0;
	while (s[i])
	{
		env_len = 0;
		if (s[i] == '$' && s[i + 1])
		{
			i++;
			if (s[i] && s[i] != '\\' && s[i] != ' ' && s[i] != '$')
			{
				env_len = env_name_len_chk(s, &i);
				if (s[i] == '?' || (s[i] >= '0' && s[i] <= '9'))
					env_len = 1;
				env_len = handle_qt(env_lset_new, env_len, e_idx, m_t);
				env_lset_new[e_idx]. len = env_len;
				e_idx++;
			}
			if (s[i] == '$')
				i--;
		}
		i++;
	}
}

void	env_len_chk(t_list *tk_list, char *token, int meta_value)
{
	t_env	*env_lset_new;
	int		env_cnt;
	int		e_idx;

	e_idx = 0;
	env_cnt = env_count_chk(token, tk_list);
	if (env_cnt)
		env_lset_new = (t_env *)malloc(sizeof(t_env) * env_cnt + 1);
	else
		return ;
	if (!env_lset_new)
		exit(1);
	env_lset_new = ini_env_lset(env_lset_new, env_cnt);
	if (tk_list -> env_lset)
	{
		e_idx = cpy_former_env_lset(env_lset_new, tk_list, e_idx);
		free(tk_list -> env_lset);
	}
	alloc_env_len(env_lset_new, token, e_idx, meta_value);
	env_lset_new[env_cnt]. len = END;
	tk_list -> env_lset = env_lset_new;
}
