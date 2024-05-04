/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeshin <jeshin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 15:15:38 by jeshin            #+#    #+#             */
/*   Updated: 2024/05/01 09:32:41y jeshin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	open_heredoc_n_return(t_subtree *subtree)
{
	char	*buf;
	char	*limiter;
	int		size_of_limiter;
	int		heredoc_fd;

	if (subtree == 0)
		return (EXIT_FAILURE);
	heredoc_fd = open(".here_doc_tmp_f", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (heredoc_fd < 0)
	{
		ft_putstr_fd("bash: ",2);
		// ft_putstr_fd(subtree->,2);
		// ft_putstr_fd(": ",2);
		perror(NULL);
		return (EXIT_FAILURE); // exit code!
		// exit(ENOENT);
	}
	limiter = subtree->infile;
	if (limiter == 0)
		return (EXIT_FAILURE);
	size_of_limiter = ft_strlen(limiter);
	while (TRUE)
	{
		buf = readline("> ");
		if (buf == 0 || ft_strncmp(buf, limiter, size_of_limiter + 1) == 0)
			break ;
		if (write(heredoc_fd, buf, ft_strlen(buf) + 1) < 0)
			return (EXIT_FAILURE);
		if (write(heredoc_fd, "\n", 1) < 0)
			return (EXIT_FAILURE);
		free(buf);
	}
	if (buf != NULL)
		free(buf);
	close(heredoc_fd);
	heredoc_fd = open(".here_doc_tmp_f", O_RDONLY);
	return (heredoc_fd);
}

static int	open_infile_n_return(t_subtree *subtree)
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
		ft_putstr_fd("bash: ",2);
		ft_putstr_fd(subtree->infile,2);
		ft_putstr_fd(": ",2);
		perror(NULL);
		exit(EXIT_FAILURE); // exit code!
		// exit(ENOENT);
	}
	return (infile_fd);
}

static int	open_outfile_n_return(t_subtree *subtree)
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
		ft_putstr_fd("bash: ",2);
		ft_putstr_fd(subtree->outfile, 2);
		ft_putstr_fd(": ",2);
		perror(NULL);
		exit(EXIT_FAILURE); // exit code!
		// exit(ENOENT);
	}
	return (outfile_fd);
}

static int	open_appending_n_return(t_subtree *subtree)
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
		ft_putstr_fd("bash: ",2);
		ft_putstr_fd(subtree->outfile, 2);
		ft_putstr_fd(": ",2);
		perror(NULL);
		exit(EXIT_FAILURE); // exit code!
		// exit(ENOENT);
	}
	return (appending_fd);
}

int	get_infile_fd(t_subtree *subtree)
{
	if (subtree == 0)
		return (STDIN_FILENO);
	if (subtree->infile == NULL)
		return (STDIN_FILENO);
	if (subtree->is_heredoc == ON)
		return (open_heredoc_n_return(subtree));
	if (subtree->is_heredoc == OFF && subtree->infile != NULL)
		return (open_infile_n_return(subtree));
	return (STDIN_FILENO);
}

int	get_outfile_fd(t_subtree *subtree)
{
	if (subtree == 0)
		return (STDOUT_FILENO);
	if (subtree->outfile == NULL)
		return (STDOUT_FILENO);
	if (subtree->is_appending == ON)
		return (open_appending_n_return(subtree));
	if (subtree->is_appending == OFF && subtree->outfile != NULL)
		return (open_outfile_n_return(subtree));
	return (STDOUT_FILENO);
}