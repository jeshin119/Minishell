/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeshin <jeshin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 16:20:36 by jeshin            #+#    #+#             */
/*   Updated: 2024/05/15 17:51:40 by jeshin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	write_line(char *filename, int heredoc_fd, char *limiter, int size)
{
	char			*buf;
	char			*bkup;

	bkup = 0;
	signal(SIGINT, handle_int_to_exit_heredoc);
	while (TRUE)
	{
		buf = readline("> ");
		if (is_file_exist(filename, buf, bkup) == EXIT_FAILURE)
			return (EXIT_FAILURE);
		if (buf == 0)
			return (end_heredoc(buf, bkup, filename, heredoc_fd));
		if (ft_strncmp(buf, limiter, size + 1) == 0)
			break ;
		buf = ft_strjoin(buf, ft_strdup("\n"));
		if (write(heredoc_fd, buf, ft_strlen_js(buf)) < 0)
		{
			ft_putstr_fd("bash: write error\n", 2);
			free_heredoc(buf, bkup, filename);
			return (EXIT_FAILURE);
		}
		make_bkup(buf, &bkup);
	}
	free_heredoc(buf, bkup, 0);
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
		perror("open :");
		g_status = 1;
		return (EXIT_FAILURE);
	}
	if (write_line(filename, heredoc_fd, limiter, ft_strlen_js(limiter)))
		return (EXIT_FAILURE);
	close(heredoc_fd);
	free(subtree->infile);
	subtree->infile = filename;
	subtree->is_heredoc = 1;
	return (EXIT_SUCCESS);
}
