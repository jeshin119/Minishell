/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeshin <jeshin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 19:35:07 by seunghan          #+#    #+#             */
/*   Updated: 2024/05/29 17:00:38 by seunghan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	token_merge(t_list *tk_list, char *str, int start, int len)
{
	if (str && tk_list -> token)
	{
		tk_list -> token = ft_strjoin(tk_list -> token, str);
		tk_list -> len += len;
	}
	else if (!str && tk_list -> token)
		return ;
	else if (!tk_list -> token && str)
	{
		tk_list -> token = str;
		tk_list -> start = start;
		tk_list -> len = len;
	}
}

void	put_str_in_tk_list(t_list *tk_list, char *str, int start, int len)
{
	if (tk_list -> tmp_flag)
	{
		tk_list -> start = start;
		tk_list -> len = len;
	}
	if (!str && !tk_list -> env_lset)
		str = ft_strdup("");
	tk_list -> token = str;
}
