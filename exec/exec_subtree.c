/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_subtree.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeshin <jeshin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 11:02:07 by jeshin            #+#    #+#             */
/*   Updated: 2024/05/07 16:43:18 by jeshin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	redirection(t_subtree *subtree, int *stdin_copy,int *stdout_copy)
{
	subtree->infile_fd = get_infile_fd(subtree);
	subtree->outfile_fd = get_outfile_fd(subtree);
	if (subtree->infile_fd != STDIN_FILENO || subtree->outfile_fd != STDOUT_FILENO)
	{
		if (stdin_copy != 0)
			*stdin_copy = dup(STDIN_FILENO);
		if (stdout_copy != 0)
			*stdout_copy = dup(STDOUT_FILENO);
		my_dup2(subtree, subtree->infile_fd, subtree->outfile_fd);
	}
}
