/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seunghan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 14:19:41 by seunghan          #+#    #+#             */
/*   Updated: 2024/05/06 15:11:30 by seunghan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_front_str(char *token, char *s, int i, int *front_len)
{
	char		*front;

	front = 0;
	if (*front_len)
	{
		if (s[i - (*front_len) - 1] == '$')
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

void	rd_empty_chk(t_tree *now, char *exp_token)
{
	if (!exp_token)
	{
		if ((now -> tk_list -> env_lset)[0]. d_quote)
			return ;
		printf("%s: ambiguous redirect\n", now -> tk_list -> token);
		now -> ambi_flag = ON;
	}
}

void	rd_space_chk(char *env, t_tree *now, int d_quote)
{
	int	i;

	if (d_quote)
		return ;
	i = 0;
	while (env[i])
	{
		if (env[i] == ' ')
		{
			printf("%s: ambiguous redirect\n", now -> tk_list -> token);
			now -> ambi_flag = ON;
		}
		i++;
	}
}
