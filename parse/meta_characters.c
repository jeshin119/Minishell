/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   meta_characters.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeshin <jeshin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 15:09:46 by seunghan          #+#    #+#             */
/*   Updated: 2024/05/15 18:31:52 by jeshin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	meta_chk(char *s, int i, int meta_value)
{
	if (meta_value == BACK_SLASH)
		return (0);
	else if (s[i] == '|')
		return (PIPE);
	else if (s[i] == '<' && s[i + 1] == '<')
		return (HERE_DOC);
	else if (s[i] == '>' && s[i + 1] == '>')
		return (D_RIGHT);
	else if (s[i] == '>')
		return (RIGHT);
	else if (s[i] == '<')
		return (LEFT);
	else if (s[i] == '\"' && quote_closed_chk(s, i))
		return (D_QUOTE);
	else if (s[i] == '\'' && quote_closed_chk(s, i))
		return (S_QUOTE);
	else if (s[i] == '\\')
		return (BACK_SLASH);
	return (0);
}

static void	quote_tokenize(char *s, t_list **tk_list, int meta_value, int *i)
{
	int		start;
	char	*str;

	start = (*i) + 1;
	*i = quote_closed_chk(s, *i);
	str = ft_substr(s, start, (*i) - start);
	if (!(*tk_list) || (*tk_list)-> ctrl_token || s[start - 2] == ' ')
	{
		if ((*tk_list) && (*tk_list)-> quote_to_space)
		{
			env_len_chk(*tk_list, str, meta_value);
			(*tk_list)-> token = ft_strjoin((*tk_list)-> token, str);
			return ;
		}
		*tk_list = ft_lstnew(*tk_list);
		(*tk_list)-> token = str;
		env_len_chk(*tk_list, str, meta_value);
	}
	else
	{
		env_len_chk(*tk_list, str, meta_value);
		(*tk_list)-> token = ft_strjoin((*tk_list)-> token, str);
	}
}

void	meta_split(char *s, t_list **tk_list, int *i)
{
	int	meta_value;

	meta_value = 0;
	meta_value = meta_chk(s, *i, meta_value);
	if (meta_value == PIPE || meta_value == LEFT || meta_value == RIGHT)
	{
		*tk_list = ft_lstnew(*tk_list);
		(*tk_list)-> token = ft_substr(s, *i, 1);
		(*tk_list)-> ctrl_token = meta_value;
	}
	else if (meta_value == D_RIGHT || meta_value == HERE_DOC)
	{
		*tk_list = ft_lstnew(*tk_list);
		(*tk_list)-> token = ft_substr(s, *i, 2);
		(*tk_list)-> ctrl_token = meta_value;
		(*i)++;
	}
	else if (meta_value == D_QUOTE || meta_value == S_QUOTE)
		quote_tokenize(s, tk_list, meta_value, i);
}
