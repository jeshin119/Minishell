/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeshin <jeshin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 16:20:36 by jeshin            #+#    #+#             */
/*   Updated: 2024/05/18 16:46:44 by jeshin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	write_heredoc(char *filename, t_subtree *subtree)
{
	char			*buf;
	char			*limiter;
	int				fd;

	limiter = subtree->infile;
	fd = subtree->infile_fd;
	while (TRUE)
	{
		buf = readline("> ");
		if (g_status == SIGINT)
			return (free_heredoc(buf, filename));
		if (exist_file(filename) == EXIT_FAILURE)
			return (free_heredoc(buf, filename));
		if (buf == 0)
			return (EXIT_SUCCESS);
		if (ft_strncmp(buf, limiter, ft_strlen_js(limiter) + 1) == 0)
			break ;
		buf = ft_strjoin(buf, ft_strdup("\n"));
		if (write(fd, buf, ft_strlen_js(buf)) < 0)
			return (free_heredoc(buf, filename));
		free(buf);
	}
	free_heredoc(buf, 0);
	return (EXIT_SUCCESS);
}

static int	open_heredoc(t_subtree *subtree, char **filename, char *limiter)
{
	if (subtree == 0)
		return (EXIT_FAILURE);
	*filename = ft_strjoin_no_free(".here_doc_", limiter);
	subtree->infile_fd = open(*filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (subtree->infile_fd < 0)
	{
		perror("open :");
		g_status = 1;
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int	get_heredoc(t_tree *tree, t_subtree *subtree)
{
	char	*filename;
	char	*limiter;

	subtree->infile = get_nth_token_from_lst(tree, tree->tk_idx_set[1]);
	limiter = subtree->infile;
	if (limiter == 0)
		return (EXIT_FAILURE);
	if (open_heredoc(subtree, &filename, limiter))
		return (EXIT_FAILURE);
	signal(SIGINT, handle_sigint_to_exit_readline);
	if (write_heredoc(filename, subtree))
		return (EXIT_FAILURE);
	close(subtree->infile_fd);
	subtree->infile_fd = 0;
	free(subtree->infile);
	subtree->infile = filename;
	subtree->is_heredoc = 1;
	signal(SIGINT, handle_sigint_in_main);
	return (EXIT_SUCCESS);
}
