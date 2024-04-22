/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_chk.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seunghan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 12:06:07 by seunghan          #+#    #+#             */
/*   Updated: 2024/04/22 12:21:12 by seunghan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	pipe_chk(t_list *tk_list)
{
	while (tk_list)
	{
		if (tk_list -> ctrl_token == PIPE)
			return (1);
		tk_list = tk_list -> next;
	}
	return (0);
}

int	right_rd_chk(t_list *tk_list)
{
	while (tk_list)
	{
		if (tk_list -> ctrl_token == RIGHT || tk_list -> ctrl_token == D_RIGHT)
			return (1);
		tk_list = tk_list -> next;
	}
	return (0);
}

int	get_double_direct(int direct)
{
	if (direct == LEFT)
		return (HERE_DOC);
	return (D_RIGHT);
}
