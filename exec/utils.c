/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeshin <jeshin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 17:46:28 by jeshin            #+#    #+#             */
/*   Updated: 2024/05/15 16:58:09 by jeshin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	free_tab(char	**tab)
{
	int	i;

	if (tab == NULL)
		return ;
	i = -1;
	while (tab[++i])
		free(tab[i]);
	free(tab);
}

char	*get_nth_token_from_lst(t_tree *tree, int nth)
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
		here = here->next;
		tmp = here->token;
	}
	if (here == 0)
		return (NULL);
	ret = ft_strdup(tmp);
	return (ret);
}

char	**get_opt_from_lst(t_tree *tree)
{
	t_list	*start;
	char	**opt;
	int		size;
	int		i;
	int		j;

	if (tree == 0 || tree->tk_list == 0)
		return (NULL);
	size = -1;
	while ((tree->tk_idx_set)[++size] >= 0)
		;
	opt = (char **)malloc(sizeof(char *) * (size + 1));
	if (opt == 0)
		perror_n_exit("malloc");
	opt[size] = 0;
	i = -1;
	start = tree->tk_list;
	while (++i < tree->tk_idx_set[0] && start)
		start = start->next;
	j = -1;
	while (++j < size)
		opt[j] = get_nth_token_from_lst(tree, i++);
	return (opt);
}

void	update_prev_status(t_dq *env)
{
	t_node	*start;

	start = env->tail;
	while (start)
	{
		if (ft_strncmp(start->name, "?", 2) == EXIT_SUCCESS)
		{
			if (start->val != 0)
				free(start->val);
			start->val = ft_itoa(g_status);
			break ;
		}
		start = start->prev;
	}
}

void	perror_n_exit(const char *str)
{
	perror(str);
	exit(EXIT_FAILURE);
}
