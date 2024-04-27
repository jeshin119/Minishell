/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeshin <jeshin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 17:46:28 by jeshin            #+#    #+#             */
/*   Updated: 2024/05/01 17:02:49 by jeshin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

void	exit_with_errmsg(char *msg)
{
	perror(msg);
	exit(EXIT_FAILURE);
}

void	free_tab(char	**tab)
{
	int	i;

	i = -1;
	while (tab[++i])
		free(tab[i]);
	free(tab);
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
	char	*tmp;
	char	*ret;
	t_list	*here;
	int		i;

	if (tree == 0 || tree->tk_list == 0)
		return (NULL);
	i = -1;
	here = tree->tk_list;
	tmp = here->token;
	while (here && ++i < nth)
	{
		here=here->next;
		tmp = here->token;
	}
	if (here == 0)
		return (NULL);
	ret = ft_strdup(tmp);
	return (ret);
}

char **get_opt_from_lst(t_tree *tree)
{
	t_list *start;
	int	size;
	int	i;
	int	j;

	if (tree == 0 || tree->tk_list == 0)
		return (NULL);
	size = -1;
	while((tree->tk_idx_set)[++size] >= 0);
	char **opt = (char **)malloc(sizeof(char *) * (size + 1));
	opt[size] = 0;
	i = -1;
	start = tree->tk_list;
	while (++i < tree->tk_idx_set[0] && start){
		start=start->next;
	}
	j = -1;
	while (++j < size)
		opt[j]=get_nth_token_from_lst(tree , i++);
	return (opt);
}

void	my_dup2(int rd, int wr)
{
	if (rd != STDIN_FILENO){
		if (dup2(rd, 0) < 0)
			perror("dup2 error");
	}
	if (wr != STDOUT_FILENO){
		if (dup2(wr, 1) < 0)
			perror("dup2 error");
	}
}

void	perr_n_exit(const char *err)
{
	perror(err);
	exit(EXIT_FAILURE);
}