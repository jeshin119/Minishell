/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeshin <jeshin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 13:15:43 by jeshin            #+#    #+#             */
/*   Updated: 2024/05/29 17:27:31 by jeshin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	open_infile(t_subtree *subtree)
{
	char	*infile;

	if (subtree == 0)
		return (EXIT_FAILURE);
	infile = subtree->infile;
	if (infile == 0)
		return (EXIT_FAILURE);
	subtree->infile_fd = open(infile, O_RDONLY);
	if (subtree->infile_fd < 0)
	{
		ft_putstr_fd("bash: ", 2);
		ft_putstr_fd(subtree->infile, 2);
		ft_putstr_fd(": ", 2);
		perror(NULL);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int	open_tmp_outfile(char *tmp, int is_appending)
{
	int		fd;

	if (tmp == NULL)
		return (EXIT_FAILURE);
	if (is_appending)
		fd = open(tmp, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else
		fd = open(tmp, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
	{
		ft_putstr_fd("bash: ", 2);
		ft_putstr_fd(tmp, 2);
		ft_putstr_fd(": ", 2);
		perror(NULL);
		return (EXIT_FAILURE);
	}
	free(tmp);
	close(fd);
	return (EXIT_SUCCESS);
}

int	open_outfile(t_subtree *sbtr, int is_appending)
{
	char	*outfile;

	if (sbtr == 0)
		return (EXIT_FAILURE);
	outfile = sbtr->outfile;
	if (outfile == 0)
		return (EXIT_FAILURE);
	if (is_appending)
		sbtr->outfile_fd = open(outfile, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else
		sbtr->outfile_fd = open(outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (sbtr->outfile_fd < 0)
	{
		ft_putstr_fd("bash: ", 2);
		ft_putstr_fd(sbtr->outfile, 2);
		ft_putstr_fd(": ", 2);
		perror(NULL);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int	get_infile_fd(t_subtree *subtree)
{
	if (!subtree)
		return (EXIT_FAILURE);
	if (subtree->infile == NULL)
	{
		subtree->infile_fd = STDIN_FILENO;
		return (EXIT_SUCCESS);
	}
	if (open_infile(subtree) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	get_outfile_fd(t_subtree *subtree)
{
	if (!subtree)
		return (EXIT_FAILURE);
	if (subtree->outfile == NULL)
	{
		subtree->outfile_fd = STDOUT_FILENO;
		return (EXIT_SUCCESS);
	}
	if (open_outfile(subtree, subtree->is_appending))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
