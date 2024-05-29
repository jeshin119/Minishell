/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_empty_chk.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seunghan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 16:39:21 by seunghan          #+#    #+#             */
/*   Updated: 2024/05/23 13:05:55 by seunghan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static char	*chk_and_empty(char *s, char *token, int *i, int *f_len)
{
	while (s[(*i)])
	{
		if (s[(*i)] == '$' && s[(*i) + 1])
		{
			if (s[(*i) + 1] != '\\' && white_chk(s[(*i)]))
			{
				if (s[(*i) + 1] != '$')
				{
					token = get_front_str(token, s, *i, f_len);
					(*i)++;
					env_name_len_chk(s, i);
					(*i)--;
					(*f_len)--;
				}
			}
		}
		(*f_len)++;
		(*i)++;
	}
	token = get_front_str(token, s, *i, f_len);
	return (token);
}

char	*empty_fenv(char *str)
{
	char	*token;
	int		front_len;
	int		i;

	if (!str)
		return (0);
	i = 0;
	front_len = 0;
	token = 0;
	token = chk_and_empty(str, token, &i, &front_len);
	free(str);
	return (token);
}
