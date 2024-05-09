/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeshin <jeshin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 15:51:27 by jeshin            #+#    #+#             */
/*   Updated: 2024/05/09 11:20:58 by jeshin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	put_all_line(char *filename)
{
	int		fd;
	char	*line;

	fd = open(filename, O_RDONLY);
	while (TRUE)
	{
		line = get_next_line(fd);
		if (line == 0)
			break ;
		write(1, line, ft_strlen_js(line) + 1);
	}
	unlink(filename);
}

static int	write_line(char *filename, int heredoc_fd, char *limiter, int size)
{
	char			*buf;
	struct termios	term;

	while (TRUE)
	{
		buf = readline("> ");
		if (buf == 0)
		{
			rl_replace_line("", 1);
			close(heredoc_fd);
			put_all_line(filename);
			return (EXIT_FAILURE);
		}
		if (ft_strncmp(buf, limiter, size + 1) == 0)
			break ;
		if (write(heredoc_fd, buf, ft_strlen_js(buf) + 1) < 0)
			return (EXIT_FAILURE);
		if (write(heredoc_fd, "\n", 1) < 0)
			return (EXIT_FAILURE);
		free(buf);
	}
	if (buf != NULL)
		free(buf);
	return (EXIT_SUCCESS);
}

int	write_heredoc(t_subtree *subtree)
{
	char	*limiter;
	int		heredoc_fd;
	char	*filename;

	if (subtree == 0)
		return (EXIT_FAILURE);
	limiter = subtree->infile;
	if (limiter == 0)
		return (EXIT_FAILURE);
	filename = ft_strjoin_no_free(".here_doc_", limiter);
	heredoc_fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (heredoc_fd < 0)
	{
		perror("heredoc :");
		g_status = 1;
		return (-1);
	}
	if (write_line(filename, heredoc_fd, limiter, ft_strlen_js(limiter)))
		return (EXIT_FAILURE);
	close(heredoc_fd);
	subtree->infile = filename;
	subtree->is_heredoc = 1;
	return (EXIT_SUCCESS);
}
