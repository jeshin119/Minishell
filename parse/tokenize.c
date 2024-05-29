/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeshin <jeshin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 16:34:38 by seunghan          #+#    #+#             */
/*   Updated: 2024/05/29 15:57:53 by seunghan         ###   ########.fr       */
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

t_list	*tokenize(char *cmd_line, int add, t_node *env_list)
{
	t_list	*tk_list;
	t_list	*tmp_tk_list;
	char	*tmp_cmd_line;

	tmp_cmd_line = ft_strdup(cmd_line);
	tk_list = 0;
	tmp_tk_list = 0;
	tmp_cmd_line = env_string_chk(tmp_cmd_line, env_list, OFF);
	tk_list = token_split(tk_list, tmp_cmd_line, OFF);
	free(tmp_cmd_line);
	give_token_idx(tk_list, add);
	tmp_cmd_line = ft_strdup(cmd_line);
	tmp_tk_list = token_split(tmp_tk_list, tmp_cmd_line, ON);
	free(tmp_cmd_line);
	give_token_idx(tmp_tk_list, add);
	chk_ambi(tk_list, tmp_tk_list, env_list, cmd_line);
	free_all(0, tmp_tk_list);
	return (tk_list);
}
