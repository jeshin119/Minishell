/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeshin <jeshin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 11:50:19 by jeshin            #+#    #+#             */
/*   Updated: 2024/04/24 12:12:16 by jeshin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/minishell.h"

int get_pipe_num_from_tree(t_tree *tree) // 파이프 개수 파악
{
	int	n;

	n = 0;
	while(tree)
	{
		if (tree->ctrl_token == PIPE)
			n++;
		tree=tree->next_right;
	}
	return (n);
}

int	**open_pipes(int num) // 개수를 인자로 받아서 파이프 배열 만들기.
{
	int **pipe_fd_tab;

	if (num == 0)
		return (EXIT_SUCCESS);
	pipe_fd_tab = (int **)malloc(sizeof (int) * num);
	if (pipe_fd_tab == 0)
		return (EXIT_FAILURE);
	int i = -1;
	while (++i < num)
	{
		pipe_fd_tab[i] = (int *)malloc(sizeof (int) * 2);
		if (pipe_fd_tab[i] == 0)
			return (EXIT_FAILURE);
		if (pipe(pipe_fd_tab[i]))
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}