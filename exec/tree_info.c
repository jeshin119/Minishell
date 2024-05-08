/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_info.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeshin <jeshin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 17:09:53 by jeshin            #+#    #+#             */
/*   Updated: 2024/05/08 13:26:57 by jeshin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	free_subtree(t_subtree *sbtr)
{
	int	i;

	if (sbtr->cmd)
	{
		free(sbtr->cmd);
		sbtr->cmd = 0;
	}
	if (sbtr->opt)
	{
		free_tab(sbtr->opt);
		sbtr->opt = 0;
	}
	if (sbtr->is_heredoc)
		unlink(sbtr->infile);
	if (sbtr->infile)
	{
		free(sbtr->infile);
		sbtr->infile = 0;
	}
	if (sbtr->outfile)
	{
		free(sbtr->outfile);
		sbtr->outfile = 0;
	}
}

void	reset_tree_info(t_tree_info *info)
{
	int			i;
	int			**tab;
	t_subtree	*start;

	if (info == 0)
		return ;
	if (info->pipe_num != 0)
	{
		tab = info->pipe_tab;
		i = -1;
		while (++i < info->pipe_num)
			free(tab[i]);
		free(tab);
		info->pipe_num = 0;
	}
	if (info->sbt_lst == 0 || info->sbt_lst->head == 0)
		return ;
	start = info->sbt_lst->head;
	while (start)
	{
		free_subtree(start);
		start = start->next;
	}
}

void	init_tree_info(t_tree *tree, t_tree_info *tree_info)
{
	tree_info->sbt_lst = (t_sbt_lst *)malloc(sizeof(t_sbt_lst));
	if (tree_info->sbt_lst == 0)
	{
		perror("malloc: ");
		exit(EXIT_FAILURE);
	}
	tree_info->sbt_lst->head = 0;
	tree_info->sbt_lst->tail = 0;
	tree_info->pipe_num = get_pipe_num_from_tree(tree);
	open_pipes(tree_info->pipe_num, &(tree_info->pipe_tab));
}
