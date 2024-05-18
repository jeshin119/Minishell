/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeshin <jeshin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 11:02:07 by jeshin            #+#    #+#             */
/*   Updated: 2024/05/18 14:06:30 by jeshin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	save_stdin_stdout(t_subtree *sbtr, int *stdin_copy, int *stdout_copy)
{
	if (sbtr->infile_fd != STDIN_FILENO && stdin_copy)
		*stdin_copy = dup(STDIN_FILENO);
	if (sbtr->outfile_fd != STDOUT_FILENO && stdout_copy)
		*stdout_copy = dup(STDOUT_FILENO);
}

void	get_back_redirection(t_subtree *sbtr, int stdin_copy, int stdout_copy)
{
	if (sbtr->infile_fd != STDIN_FILENO)
	{
		dup2(stdin_copy, STDIN_FILENO);
		close(sbtr->infile_fd);
	}
	if (sbtr->outfile_fd != STDOUT_FILENO)
	{
		dup2(stdout_copy, STDOUT_FILENO);
		close(sbtr->outfile_fd);
	}
}

int	redirection(t_subtree *subtree, int *stdin_copy, int *stdout_copy)
{
	if (has_subtree_no_infile(subtree))
	{
		put_subtree_has_nofile_err_msg(subtree);
		g_status = 1;
		return (EXIT_FAILURE);
	}
	if (get_infile_fd(subtree))
	{
		g_status = 1;
		return (EXIT_FAILURE);
	}
	if (get_outfile_fd(subtree))
	{
		g_status = 1;
		return (EXIT_FAILURE);
	}
	save_stdin_stdout(subtree, stdin_copy, stdout_copy);
	my_dup2(subtree, subtree->infile_fd, subtree->outfile_fd);
	return (EXIT_SUCCESS);
}
