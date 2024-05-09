/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeshin <jeshin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 15:51:27 by jeshin            #+#    #+#             */
/*   Updated: 2024/05/09 17:50:03 by jeshin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	put_bkup(char *filename, int fd, char *bkup)
{
	write(1, "\033[1A", 4);
	write(1, "\033[2C", 4);
	close(fd);
	write(1, bkup, ft_strlen_js(bkup));
	unlink(filename);
}

static void	make_bkup(char **bkup, char *buf)
{
	char	*tmp;

	tmp = ft_strjoin_no_free(*bkup, buf);
	*bkup = ft_strjoin_no_free(tmp, "\n");
	free(tmp);
}

static void	free_buf_bkup(char *buf, char *bkup)
{
	if (buf != NULL)
		free(buf);
	if (bkup != NULL)
		free(bkup);
}

static int	write_line(char *filename, int heredoc_fd, char *limiter, int size)
{
	char			*buf;
	char			*bkup;
	struct termios	term;

	bkup = 0;
	while (TRUE)
	{
		buf = readline("> ");
		if (buf == 0)
		{
			put_bkup(filename, heredoc_fd, bkup);
			return (EXIT_FAILURE);
		}
		if (ft_strncmp(buf, limiter, size + 1) == 0)
			break ;
		write(heredoc_fd, buf, ft_strlen_js(buf));
		write(heredoc_fd, "\n", 1);
		make_bkup(&bkup, buf);
		free(buf);
	}
	free_buf_bkup(buf, bkup);
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
