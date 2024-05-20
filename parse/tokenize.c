/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeshin <jeshin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 16:34:38 by seunghan          #+#    #+#             */
/*   Updated: 2024/05/20 15:24:59 by jeshin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	give_token_idx(t_list *tk_list, int add)
{
	static int	idx_s;

	if (!add)
		idx_s = 0;
	while (tk_list)
	{
		tk_list -> token_idx = idx_s;
		idx_s++;
		tk_list = tk_list -> next;
	}
}

t_list	*tokenize(char *cmd_line, int add)
{
	t_list	*tk_list;
	char	*one_use_cmd_line;

	one_use_cmd_line = ft_strdup(cmd_line);
	tk_list = 0;
	tk_list = token_split(tk_list, one_use_cmd_line);
	give_token_idx(tk_list, add);
	free(one_use_cmd_line);
	return (tk_list);
}
