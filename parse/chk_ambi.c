/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chk_ambi.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seunghan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 12:11:12 by seunghan          #+#    #+#             */
/*   Updated: 2024/05/29 11:52:44 by seunghan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	chk_empty_or_white(t_list *tkl, t_list *tmp_tkl, char *s)
{
	int	e_idx;

	e_idx = 0;
	if (!tkl -> token)
	{
		tkl -> ambi_flag = ON;
		tkl -> token = ft_strdup(tmp_tkl -> token);
	}
	else
	{
		if (!tmp_tkl -> env_lset)
			return ;
		while (tmp_tkl -> env_lset[e_idx]. len > 0)
		{
			if (tmp_tkl -> env_lset[e_idx]. white_flag)
			{
				tkl -> ambi_flag = ON;
				free(tkl -> token);
				tkl -> token = ft_substr(s, tmp_tkl -> start, tmp_tkl -> len);
				return ;
			}
			e_idx++;
		}
	}
}

void	chk_ambi(t_list *tkl, t_list *tmp_tkl, t_node *env_list, char *cmd_line)
{
	while (tkl && tmp_tkl)
	{
		if (tkl -> ctrl_token >= LEFT && tkl -> ctrl_token <= D_RIGHT)
		{
			tkl = tkl -> next;
			if (!tkl)
				return ;
			while (tmp_tkl)
			{
				if (tmp_tkl -> ctrl_token >= 2 && tmp_tkl -> ctrl_token <= 5)
				{
					tmp_tkl = tmp_tkl -> next;
					if (!tmp_tkl)
						return ;
					env_white_chk(tmp_tkl, env_list);
					chk_empty_or_white(tkl, tmp_tkl, cmd_line);
					break ;
				}
				tmp_tkl = tmp_tkl -> next;
			}
		}
		tkl = tkl -> next;
	}
}
