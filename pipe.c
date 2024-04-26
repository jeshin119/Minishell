/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeshin <jeshin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 11:50:19 by jeshin            #+#    #+#             */
/*   Updated: 2024/04/26 15:27:12 by jeshin           ###   ########.fr       */
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

int	open_pipes(int num,	int ***pipe_fd_tab)
{
	int	**tab;
	int	i;

	if (num == 0)
		return (EXIT_SUCCESS);
	*pipe_fd_tab = (int **)malloc(sizeof(int *) * num);
	tab = *pipe_fd_tab;
	if (tab == 0)
		return (EXIT_FAILURE);
	i = -1;
	while (++i < num)
	{
		tab[i] = (int *)malloc(sizeof (int) * 2);
		if (tab[i] == 0)
			return (EXIT_FAILURE);
		if (pipe(tab[i]))
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
