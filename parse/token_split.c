/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_split.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeshin <jeshin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 18:03:38 by seunghan          #+#    #+#             */
/*   Updated: 2024/05/29 12:50:29 by jeshin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	change_to_space(char *s, t_list **tk_list, int i)
{
	int	meta_value;

	meta_value = 0;
	meta_value = meta_chk(s, i + 1, meta_value);
	i++;
	if (meta_value != BACK_SLASH)
		meta_split(s, tk_list, &i);
	if (meta_value >= ENV && white_chk(s[i + 1]))
		(*tk_list)-> quote_to_space = ON;
	s[i] = ' ';
	i--;
	return (i);
}

static t_list	*quote_to_space_chk(t_list *tk_list, char *str, int st, int len)
{
	if (!tk_list || !tk_list -> quote_to_space)
	{
		tk_list = ft_lstnew(tk_list);
		str = env_len_and_empty(tk_list, str, 0);
		put_str_in_tk_list(tk_list, str, st, len);
	}
	else
	{
		str = env_len_and_empty(tk_list, str, 0);
		token_merge(tk_list, str, st, len);
		tk_list -> quote_to_space = OFF;
	}
	return (tk_list);
}

static t_list	*split_words(char *s, t_list *tk_list, int i)
{
	int		j;
	int		mt_value;
	char	*str;

	mt_value = 0;
	while (s[i])
	{
		mt_value = meta_chk(s, i + 1, mt_value);
		if (!white_chk(s[i]) && s[i + 1] && white_chk(s[i + 1]) && mt_value < 2)
		{
			j = 0;
			while (s[i + 1] && white_chk(s[i + 1]) && mt_value < 2)
			{
				i++;
				j++;
				mt_value = meta_chk(s, i + 1, mt_value);
			}
			str = ft_substr(s, i + 1 - j, j);
			tk_list = quote_to_space_chk(tk_list, str, i + 1 - j, j);
		}
		if (mt_value)
			i = change_to_space(s, &tk_list, i);
		i++;
	}
	return (tk_list);
}

static int	split_first_word(char *s, t_list **tk_list)
{
	int		i;
	int		meta_value;

	i = 0;
	meta_value = 0;
	meta_value = meta_chk(s, i, meta_value);
	if (white_chk(s[0]) && s[0] != '\0' && meta_value < 2)
	{
		while (white_chk(s[i]) && s[i] != '\0' && meta_value < 2)
		{
			i++;
			meta_value = meta_chk(s, i, meta_value);
		}
		*tk_list = quote_to_space_chk(*tk_list, ft_substr(s, 0, i), 0, i);
	}
	if (meta_value)
	{
		i = change_to_space(s, tk_list, --i);
		i++;
	}
	return (i);
}

t_list	*token_split(t_list *tk_list, char *s, int tmp_flag)
{
	int	i;

	i = split_first_word(s, &tk_list);
	if (tk_list && tmp_flag)
		tk_list -> tmp_flag = ON;
	tk_list = split_words(s, tk_list, i);
	while (tk_list && tk_list -> prev)
		tk_list = tk_list -> prev;
	return (tk_list);
}
