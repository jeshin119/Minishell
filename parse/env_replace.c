/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_replace.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeshin <jeshin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 12:46:22 by seunghan          #+#    #+#             */
/*   Updated: 2024/04/22 15:17:08 by jeshin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	name_len_chk(char *s, int *i)
{
	int	name_len;
	int	j;

	j = *i;
	name_len = 1;
	if (s[j] < 'A' || (s[j] > 'Z' && s[j] < 'a') || s[j] > 'z')
	{
		if (s[j] != '_')
			return (name_len);
	}
	while (s[j])
	{
		if ((s[j] >= 'A' && s[j] <= 'Z') || (s[j] >= 'a' && s[j] <= 'z'))
			name_len++;
		else if ((s[j] >= '0' && s[j] <= '9') || s[j] == '_')
			name_len++;
		else
			break ;
		j++;
		(*i)++;
	}
	return (name_len);
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

void	env_replace(char *s, t_list **tk_list, t_node *env_list, int *i)
{
	int	name_len;
	int	val_len;
	int	start;

	val_len = 0;
	start = ++*i;
	name_len = name_len_chk(s, i);
	env_list = env_name_chk(s, env_list, start);
	if (!env_list)
		return ;
	while ((env_list -> val)[val_len])
		val_len++;
	*tk_list = ft_lstnew(*tk_list);
	(*tk_list)-> token = ft_substr(env_list -> val, 0, val_len);
}
