/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeshin <jeshin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 11:50:19 by jeshin            #+#    #+#             */
/*   Updated: 2024/05/02 17:13:08 by jeshin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/minishell.h"

int	get_pipe_num_from_tree(t_tree *tree)
{
	int	n;

	n = 0;
	while (tree)
	{
		if (tree->ctrl_token == PIPE)
			n++;
		tree = tree->next_right;
	}
	return (n);
}

void	open_pipes(int num,	int ***pipe_fd_tab)
{
	int	**tab;
	int	i;

	if (num == 0)
		return ;
	*pipe_fd_tab = (int **)malloc(sizeof(int *) * num);
	if (*pipe_fd_tab == 0)
	{
		perror("malloc: ");
		exit (EXIT_FAILURE);
	}
	tab = *pipe_fd_tab;
	i = -1;
	while (++i < num)
	{
		tab[i] = (int *)malloc(sizeof (int) * 2);
		if (tab[i] == 0)
		{
			perror("malloc: ");
			exit (EXIT_FAILURE);
		}
		if (pipe(tab[i]))
		{
			perror("pipe: ");
			exit (EXIT_FAILURE);
		}
	}
}

void	close_all_pipe(int size, int **pipe_tab)
{
	int	i;

	i = -1;
	while (++i < size)
	{
		close(pipe_tab[i][0]);
		close(pipe_tab[i][1]);
	}
}
