/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeshin <jeshin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 17:46:28 by jeshin            #+#    #+#             */
/*   Updated: 2024/04/24 11:59:32 by jeshin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

char *get_nth_token_from_lst(t_tree *tree, int nth)
{
	char	*ret;
	t_list	*here;
	int		i;
	//아 tree의 멤버변수인 tk_lst를 처음부터 하지말걸 그랬나? 반복문 낭비가 조금 있는디
	if (tree == 0 || tree->tk_list == 0)
		return (NULL);
	i = -1;
	here = tree->tk_list;
	ret = here->token;
	while (here && ++i < nth)
	{
		ret = here->token;
		here=here->next;
	}
	if (here == 0)
		return (NULL);
	return (ret);
}

void	make_my_env(char **e, t_dq *env)
{
	char	**tmp;

	init_dq(env);
	while (*e)
	{
		tmp = ft_split(*e, '=');
		push_back_dq(env, tmp[0], tmp[1]);
		free(tmp);
		e++;
	}
}

void	my_dup2(int rd, int wr)
{
	if (dup2(rd, 0) < 0)
		perror("dup2 error");
	if (dup2(wr, 1) < 0)
		perror("dup2 error");
}