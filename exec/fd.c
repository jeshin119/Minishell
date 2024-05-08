/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeshin <jeshin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 13:15:43 by jeshin            #+#    #+#             */
/*   Updated: 2024/05/08 18:13:17 by jeshin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	open_infile_n_return(t_subtree *subtree)
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
		exit(EXIT_FAILURE);
	}
	return (infile_fd);
}

int	open_outfile_n_return(t_subtree *subtree)
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
		exit(EXIT_FAILURE);
	}
	return (outfile_fd);
}

int	open_appending_n_return(t_subtree *subtree)
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
		perror(NULL);
		exit(EXIT_FAILURE);
	}
	return (appending_fd);
}
