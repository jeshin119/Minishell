/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_heredoc_chk.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seunghan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 15:29:37 by seunghan          #+#    #+#             */
/*   Updated: 2024/05/29 12:11:25 by seunghan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_node	*chk_env(t_env *env_lset, char *s, int i, t_node *env_list)
{
	static int	e_idx;
	int			env_len;
	int			idx;
	int			j;

	env_len = env_lset[e_idx]. len;
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
	if (env_lset[e_idx]. len == END)
		e_idx = 0;
	return (env_list);
}

static char	*expansion(char *token, t_env *env_lset, int *i, t_node *env_list)
{
	static int	e_idx;
	char		*env;

	if (!env_list)
	{
		e_idx++;
		if (env_lset[e_idx]. len == END)
			e_idx = 0;
		return (token);
	}
	env = ft_strdup(env_list -> val);
	*i += env_lset[e_idx]. len;
	if (token && env)
		token = ft_strjoin(token, env);
	e_idx++;
	if (env_lset[e_idx]. len == END)
		e_idx = 0;
	if (!token && env)
		return (env);
	return (token);
}

static char	*env_exp(t_env *env_lset, t_node *env_list, char *s, int i)
{
	t_node	*env_list_now;
	char	*token;
	int		front_len;

	front_len = 0;
	token = 0;
	if (!s)
		return (token);
	while (s[i])
	{
		if (s[i] == '$' && s[i + 1])
		{
			if (s[i + 1] != '\\' && white_chk(s[i]) && s[i + 1] != '$')
			{
				token = get_front_str(token, s, i, &front_len);
				env_list_now = chk_env(env_lset, s, i, env_list);
				token = expansion(token, env_lset, &i, env_list_now);
				front_len--;
			}
		}
		front_len++;
		i++;
	}
	token = get_front_str(token, s, i, &front_len);
	return (token);
}

t_env	*env_len_chk(char *input, int hd_flag)
{
	t_env	*env_lset;
	int		env_cnt;
	int		e_idx;

	e_idx = 0;
	if (!input)
		return (0);
	env_cnt = env_count_chk(input);
	if (env_cnt)
		env_lset = (t_env *)malloc(sizeof(t_env) * (env_cnt + 1));
	else
		return (0);
	if (!env_lset)
		exit(1);
	env_lset = ini_env_lset(env_lset, env_cnt);
	alloc_env_len(env_lset, input, e_idx, hd_flag);
	env_lset[env_cnt]. len = END;
	return (env_lset);
}

char	*env_string_chk(char *input, t_node *env_list, int hd_flag)
{
	t_env	*env_lset;
	char	*exp_input;
	int		i;

	if (!input || !env_list)
		return (0);
	env_lset = 0;
	exp_input = 0;
	i = 0;
	input = malloc_readline(input);
	env_lset = env_len_chk(input, hd_flag);
	if (env_lset)
	{
		exp_input = env_exp(env_lset, env_list, input, i);
		free(env_lset);
		free(input);
		if (exp_input)
			return (exp_input);
		else
			return (ft_strdup(""));
	}
	return (input);
}
