/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_fd.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeshin <jeshin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 13:15:43 by jeshin            #+#    #+#             */
/*   Updated: 2024/05/08 15:44:21 by jeshin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	b_open_infile_n_return(t_subtree *subtree)
{
	char	*infile;
	int		infile_fd;

	if (subtree == 0)
		return (EXIT_FAILURE);
	infile = subtree->infile;
	if (infile == 0)
		return (EXIT_FAILURE);
	infile_fd = open(infile, O_RDONLY);
	if (infile_fd < 0)
	{
		ft_putstr_fd("bash: ", 2);
		ft_putstr_fd(subtree->infile, 2);
		ft_putstr_fd(": ", 2);
		perror(NULL);
		return (-1);
	}
	return (infile_fd);
}

static int	b_open_outfile_n_return(t_subtree *subtree)
{
	char	*outfile;
	int		outfile_fd;

	if (subtree == 0)
		return (EXIT_FAILURE);
	outfile = subtree->outfile;
	if (outfile == 0)
		return (EXIT_FAILURE);
	outfile_fd = open(outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (outfile_fd < 0)
	{
		ft_putstr_fd("bash: ", 2);
		ft_putstr_fd(subtree->outfile, 2);
		ft_putstr_fd(": ", 2);
		perror(NULL);
		return (-1);
	}
	return (outfile_fd);
}

static int	b_open_appending_n_return(t_subtree *subtree)
{
	char	*appending;
	int		appending_fd;

	if (subtree == 0)
		return (EXIT_FAILURE);
	appending = subtree->outfile;
	if (appending == 0)
		return (EXIT_FAILURE);
	appending_fd = open(appending, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (appending_fd < 0)
	{
		ft_putstr_fd("bash: ", 2);
		ft_putstr_fd(subtree->outfile, 2);
		ft_putstr_fd(": ", 2);
		perror_n_exit(NULL);
		return (-1);
	}
	return (appending_fd);
}

int	b_get_infile_fd(t_subtree *subtree)
{
	if (subtree == 0)
		return (STDIN_FILENO);
	if (subtree->infile == NULL)
		return (STDIN_FILENO);
	if (subtree->is_heredoc == ON)
		return (b_open_infile_n_return(subtree));
	if (subtree->is_heredoc == OFF && subtree->infile != NULL)
		return (b_open_infile_n_return(subtree));
	return (STDIN_FILENO);
}

int	b_get_outfile_fd(t_subtree *subtree)
{
	if (subtree == 0)
		return (STDOUT_FILENO);
	if (subtree->outfile == NULL)
		return (STDOUT_FILENO);
	if (subtree->is_appending == ON)
		return (b_open_appending_n_return(subtree));
	if (subtree->is_appending == OFF && subtree->outfile != NULL)
		return (b_open_outfile_n_return(subtree));
	return (STDOUT_FILENO);
}