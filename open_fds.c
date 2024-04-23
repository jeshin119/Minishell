/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_fds.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeshin <jeshin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 15:15:38 by jeshin            #+#    #+#             */
/*   Updated: 2024/04/24 14:35:21 by jeshin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	open_heredoc_n_return(t_tree *tree)
{
	char	*buf;
	char	*limiter;
	int		size_of_limiter;
	int		heredoc_fd;

	heredoc_fd = open(".here_doc_tmp_f", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (heredoc_fd < 0)
		exit (EXIT_FAILURE); // exitcode뭐노?
	limiter = get_nth_token_from_lst(tree, 1);
	if (limiter == 0)
		return (EXIT_FAILURE);
	size_of_limiter = ft_strlen(limiter);
	while (TRUE)
	{
		buf = get_next_line(0);
		if (ft_strncmp(buf, limiter,size_of_limiter+1) == 0)
			break ;
		if (write(heredoc_fd, buf, ft_strlen(buf)) < 0)
			exit (EXIT_FAILURE); // exitcode뭐?
		free(buf);
	}
	return (heredoc_fd);
}

int	open_infile_n_return(t_tree *tree)
{
	char	*infile;
	int		infile_fd;

	infile = get_nth_token_from_lst(tree, 1);
	if (infile == 0)
		return (EXIT_FAILURE);
	infile_fd = open(infile, O_RDONLY);
	if (infile_fd < 0)
		exit(EXIT_FAILURE); // exit code필요
	return (infile_fd);
}

int	open_outfile_n_return(t_tree *tree)
{
	char	*outfile;
	int		outfile_fd;

	outfile = get_nth_token_from_lst(tree, 1);
	if (outfile == 0)
		return (EXIT_FAILURE);
	outfile_fd = open(outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (outfile_fd < 0)
		exit(EXIT_FAILURE); // exit code필요
	return (outfile_fd);
}

int	open_appending_n_return(t_tree *tree)
{
	char	*appending;
	int		appending_fd;

	appending = get_nth_token_from_lst(tree, 1);
	if (appending == 0)
		return (EXIT_FAILURE);
	appending_fd = open(appending, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (appending_fd < 0)
		exit(EXIT_FAILURE); // exit code필요
	return (appending_fd);
}