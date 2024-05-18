/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeshin <jeshin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 15:51:27 by jeshin            #+#    #+#             */
/*   Updated: 2024/05/18 13:31:43 by jeshin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	check_already_has_heredoc(t_subtree *new)
{
	if (new->is_heredoc)
	{
		if (new->infile)
			unlink(new->infile);
		if (new->infile)
			free(new->infile);
		new->infile = 0;
		new->is_heredoc = 0;
	}
}

int	free_heredoc(char *buf, char *filename)
{
	if (buf)
	{
		free(buf);
		buf = 0;
	}
	if (filename)
	{
		if (g_status == SIGINT)
			unlink(filename);
		free(filename);
		filename = 0;
	}
	return (EXIT_FAILURE);
}

int	exist_file(char *filename)
{
	int				tmp_fd;

	tmp_fd = open(filename, O_RDONLY);
	if (tmp_fd < 0)
	{
		ft_putstr_fd("bash: no heredoc file\n", 2);
		return (EXIT_FAILURE);
	}
	else
		close(tmp_fd);
	return (EXIT_SUCCESS);
}
