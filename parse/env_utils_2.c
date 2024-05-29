/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeshin <jeshin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 14:19:41 by seunghan          #+#    #+#             */
/*   Updated: 2024/05/29 12:49:11 by jeshin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*get_front_str(char *token, char *s, int i, int *front_len)
{
	char		*front;

	front = 0;
	if (*front_len)
	{
		if ((i - (*front_len) - 1) >= 0 && s[i - (*front_len) - 1] == '$')
			(*front_len)++;
		front = (char *)malloc(*front_len + 1);
		if (!front)
			exit(1);
		front[*front_len] = 0;
		while (*front_len)
		{
			(*front_len)--;
			i--;
			front[*front_len] = s[i];
		}
		if (token && front)
			token = ft_strjoin(token, front);
		else if (!token && front)
			return (front);
	}
	return (token);
}

t_node	*chk_valid_env(t_tree *now, char *s, int i, t_node *env_list)
{
	static int	e_idx;
	int			env_len;
	int			idx;
	int			j;

	env_len = (now -> tk_list -> env_lset)[e_idx]. len;
	while (env_list)
	{
		j = 0;
		idx = i + 1;
		while ((env_list -> name)[j] && j <= env_len)
		{
			if ((env_list -> name)[j] != s[idx])
				break ;
			j++;
			idx++;
		}
		if (j && j == env_len && !(env_list -> name)[j])
			break ;
		env_list = env_list -> next;
	}
	e_idx++;
	if ((now -> tk_list -> env_lset)[e_idx]. len == END)
		e_idx = 0;
	return (env_list);
}

void	is_there_white(t_list *tk_list, t_node *env_list, int i, int e_idx)
{
	char	*s;
	char	*env_val;
	int		d_quote;
	int		j;

	d_quote = 0;
	j = 0;
	i--;
	if (!tk_list -> env_lset)
		return ;
	d_quote = tk_list -> env_lset[e_idx]. d_quote;
	s = tk_list -> token;
	env_list = chk_env(tk_list -> env_lset, s, i, env_list);
	if (!env_list)
		return ;
	env_val = env_list -> val;
	while (env_val[j])
	{
		if (!d_quote && white_chk(env_val[j]))
			tk_list -> env_lset[e_idx]. white_flag = ON;
		j++;
	}
}

void	env_white_chk(t_list *tk_list, t_node *env_list)
{
	char	*s;
	int		i;
	int		e_idx;

	e_idx = 0;
	i = 0;
	s = tk_list -> token;
	if (!s)
		return ;
	while (s[i])
	{
		if (s[i] == '$' && s[i + 1])
		{
			i++;
			if (s[i] && s[i] != '\\' && white_chk(s[i]) && s[i] != '$')
			{
				is_there_white(tk_list, env_list, i, e_idx);
				e_idx++;
			}
			if (s[i] == '$')
				i--;
		}
		if (s[i])
			i++;
	}
}

char	*env_len_and_empty(t_list *tk_list, char *str, int meta_value)
{
	if (tk_list && tk_list -> prev && tk_list -> prev -> tmp_flag)
		tk_list -> tmp_flag = ON;
	if (!tk_list -> env_lset)
		tk_list -> env_lset = env_len_chk(str, 0);
	else
		add_env_lset(tk_list, env_len_chk(str, 0));
	if (!tk_list -> tmp_flag && meta_value != S_QUOTE)
		str = empty_fenv(str);
	return (str);
}
