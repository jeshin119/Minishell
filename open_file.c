/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeshin <jeshin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 15:15:38 by jeshin            #+#    #+#             */
/*   Updated: 2024/04/26 16:28:10 by jeshin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

static int	open_heredoc_n_return(t_tree *tree)
{
	char	*buf;
	char	*limiter;
	int		size_of_limiter;
	int		heredoc_fd;

	if (tree == 0 || tree->tk_idx_set == 0)
		return (EXIT_FAILURE);
	heredoc_fd = open(".here_doc_tmp_f", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (heredoc_fd < 0)
		exit (EXIT_FAILURE); //errcde!
	limiter = get_nth_token_from_lst(tree, tree->tk_idx_set[1]);
	if (limiter == 0)
		return (EXIT_FAILURE);
	size_of_limiter = ft_strlen(limiter);
	while (TRUE)
	{
		buf = get_next_line(0);
		if (ft_strncmp(buf, limiter, size_of_limiter + 1) == 0)
			break ;
		if (write(heredoc_fd, buf, ft_strlen(buf)) < 0)
			exit (EXIT_FAILURE); // exitcode!
		free(buf);
	}
	return (heredoc_fd);
}

static int	open_infile_n_return(t_tree *tree)
{
	char	*infile;
	int		infile_fd;

	if (tree == 0 || tree->tk_idx_set == 0)
		return (EXIT_FAILURE);
	infile = get_nth_token_from_lst(tree, tree->tk_idx_set[1]);
	if (infile == 0)
		return (EXIT_FAILURE);
	infile_fd = open(infile, O_RDONLY);
	if (infile_fd < 0)
	{
		perror("infile error : file not found");
		exit(EXIT_FAILURE); // exit code!
	}
	return (infile_fd);
}

static int	open_outfile_n_return(t_tree *tree)
{
	char	*outfile;
	int		outfile_fd;

	if (tree == 0 || tree->tk_idx_set == 0)
		return (EXIT_FAILURE);
	outfile = get_nth_token_from_lst(tree, tree->tk_idx_set[1]);
	if (outfile == 0)
		return (EXIT_FAILURE);
	outfile_fd = open(outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (outfile_fd < 0)
		exit(EXIT_FAILURE); // exit cod!
	return (outfile_fd);
}

static int	open_appending_n_return(t_tree *tree)
{
	char	*appending;
	int		appending_fd;

	if (tree == 0 || tree->tk_idx_set == 0)
		return (EXIT_FAILURE);
	appending = get_nth_token_from_lst(tree, tree->tk_idx_set[1]);
	if (appending == 0)
		return (EXIT_FAILURE);
	appending_fd = open(appending, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (appending_fd < 0)
		exit(EXIT_FAILURE); // exit code!
	return (appending_fd);
}

int	get_fd(t_tree *tree)
{
	if (tree == 0)
		return (EXIT_FAILURE);
	if (tree->ctrl_token == PIPE)
		return (EXIT_SUCCESS);
	if (tree->ctrl_token == HERE_DOC)
		return (open_heredoc_n_return(tree));
	if (tree->ctrl_token == LEFT)
		return (open_infile_n_return(tree));
	if (tree->ctrl_token == RIGHT)
		return (open_outfile_n_return(tree));
	if (tree->ctrl_token == D_RIGHT)
		return (open_appending_n_return(tree));
	return (EXIT_FAILURE);
}
