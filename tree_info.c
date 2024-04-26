/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_info.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeshin <jeshin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 17:09:53 by jeshin            #+#    #+#             */
/*   Updated: 2024/04/26 16:32:07 by jeshin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/minishell.h"

int init_tree_info(t_tree *tree, t_tree_info *tree_info)
{
	tree_info->sbt_lst = (t_sbt_lst *)malloc(sizeof(t_sbt_lst));
	tree_info->pipe_num = get_pipe_num_from_tree(tree); // 파이프 수 구하기.
	if (open_pipes(tree_info->pipe_num,&(tree_info->pipe_tab))) // 파이프 수만큼 파이프를 열어놓음.
		return (EXIT_FAILURE);
	tree_info->sbt_lst->head = 0;
	tree_info->sbt_lst->tail = 0;
	return (EXIT_SUCCESS);
}

void	reset_tree_info(t_tree_info *info)
{
	int	i;
	int	**tab;
	t_subtree *start;

	if (info == 0)
		return ;
	if (info->pipe_num!=0)
	{
		tab = info->pipe_tab;
		i = -1;
		while(++i<info->pipe_num)
			free(tab[i]);
		free(tab);
		info->pipe_num=0;
	}
	if (info->sbt_lst == 0 || info->sbt_lst->head == 0)
		return ;
	start = info->sbt_lst->head;
	while(start)
	{
		free_subtree(start);
		start = start->next;
	}
}