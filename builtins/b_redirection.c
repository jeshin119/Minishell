/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_redirection.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeshin <jeshin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 15:21:37 by jeshin            #+#    #+#             */
/*   Updated: 2024/05/08 15:27:35 by jeshin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	b_redirection(t_subtree *subtree, int *stdin_copy, int *stdout_copy)
{
	subtree->infile_fd = b_get_infile_fd(subtree);
	if (subtree->infile_fd == -1)
		return (EXIT_FAILURE);
	subtree->outfile_fd = b_get_outfile_fd(subtree);
	if (subtree->outfile_fd == -1)
		return (EXIT_FAILURE);
	if (subtree->infile_fd != STDIN_FILENO || \
	subtree->outfile_fd != STDOUT_FILENO)
	{
		if (stdin_copy != 0)
			*stdin_copy = dup(STDIN_FILENO);
		if (stdout_copy != 0)
			*stdout_copy = dup(STDOUT_FILENO);
		my_dup2(subtree, subtree->infile_fd, subtree->outfile_fd);
	}
	return (EXIT_SUCCESS);
}
