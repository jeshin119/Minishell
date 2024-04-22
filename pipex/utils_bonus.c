/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeshin <jeshin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 17:46:28 by jeshin            #+#    #+#             */
/*   Updated: 2024/04/22 15:30:59 by jeshin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex_bonus.h"

void	exit_with_errmsg(char *msg)
{
	perror(msg);
	exit(EXIT_FAILURE);
}

void	free_tab(char	***tab)
{
	int	i;

	i = -1;
	while ((*tab)[++i])
		free((*tab)[i]);
	free(*tab);
}

void	free_all(t_ags	*ags)
{
	int	i;

	i = -1;
	while (++i < ags->n_cmd -1)
		free(ags->pipe_fd_tab[i]);
	free(ags->pipe_fd_tab);
	i = -1;
	while (ags->opts_tab[++i] != 0)
	{
		free_tab(&ags->opts_tab[i]);
	}
	free(ags->opts_tab);
	if (ags->is_here_doc)
		unlink(".here_doc_tmp_f");
}

void	init_str_agr(t_str_ags *chunk)
{
	chunk->dq = 0;
	chunk->sq = 0;
	chunk->i = 0;
	chunk->pos = 0;
	chunk->have_lst_made = 0;
	chunk->tmp_s = 0;
}

int	get_mid_substr(char *s, char **ret, int i, int pos)
{
	if (i > 0 && s[i - 1] == '\'' && s[pos] == '\'')
		*ret = ft_substr(s, pos + 1, i - 2 - pos);
	else if (i > 0 && s[i - 1] == '"' && s[pos] == '"')
		*ret = ft_substr(s, pos + 1, i - 2 - pos);
	else
		*ret = ft_substr(s, pos, i - pos);
	if (*ret)
		return (1);
	return (0);
}
