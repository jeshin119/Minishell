/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_chk.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seunghan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 12:46:22 by seunghan          #+#    #+#             */
/*   Updated: 2024/05/02 18:54:55 by seunghan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*expansion(char *token, t_tree *now, int *i, t_node *env_list)
{
	static int	e_idx;
	char		*env;

	env_list = chk_valid_env(now, now -> tk_list -> token, *i, env_list);
	if (!env_list)
	{
		*i += (now -> tk_list -> env_lset)[e_idx]. len;
		e_idx++;
		if ((now -> tk_list -> env_lset)[e_idx]. len == END)
			e_idx = 0;
		return (token);
	}
	env = ft_strdup(env_list -> val);
	if (now -> ctrl_token >= LEFT && now -> ctrl_token <= D_RIGHT)
		rd_space_chk(env, now, (now -> tk_list -> env_lset)[e_idx]. d_quote);
	*i += (now -> tk_list -> env_lset)[e_idx]. len;
	if (token && env)
		token = ft_strjoin(token, env);
	e_idx++;
	if ((now -> tk_list -> env_lset)[e_idx]. len == END)
		e_idx = 0;
	if (!token && env)
		return (env);
	return (token);
}

static char	*env_exp(t_tree *now, t_node *env_list, char *s)
{
	char	*token;
	int		front_len;
	int		i;

	i = 0;
	front_len = 0;
	token = 0;
	if (!s)
		return (token);
	while (s[i])
	{
		if (s[i] == '$' && s[i + 1])
		{
			if (s[i + 1] != '\\' && s[i + 1] != ' ' && s[i + 1] != '$')
			{
				token = get_front_str(token, s, i, &front_len);
				token = expansion(token, now, &i, env_list);
				front_len--;
			}
		}
		front_len++;
		i++;
	}
	token = get_front_str(token, s, i, &front_len);
	return (token);
}

void	env_chk(t_tree *now, t_node *env_list)
{
	t_list	*head;
	char	*exp_token;
	int		i;

	if (!now || !now -> tk_idx_set)
		return ;
	i = 0;
	head = now -> tk_list;
	while (now -> tk_list)
	{
		now -> tk_list = mv_to_valid_token(now, i);
		if (now -> tk_list && now -> tk_list -> env_lset)
		{
			exp_token = env_exp(now, env_list, now -> tk_list -> token);
			if (now -> ctrl_token >= LEFT && now -> ctrl_token <= D_RIGHT)
				rd_empty_chk(now, exp_token);
			free(now -> tk_list -> token);
			now -> tk_list -> token = exp_token;
		}
		i++;
	}
	now -> tk_list = head;
}
