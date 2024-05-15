/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeshin <jeshin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 15:51:27 by jeshin            #+#    #+#             */
/*   Updated: 2024/05/15 20:02:46 by jeshin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	free_heredoc(char *buf, char *bkup, char *filename)
{
	if (buf != NULL)
	{
		free(buf);
		buf = 0;
	}
	if (bkup != NULL)
	{
		free(bkup);
		bkup = 0;
	}
	if (filename != NULL)
	{
		if (g_status == SIGINT)
			unlink(filename);
		free(filename);
		filename = 0;
	}
	return (EXIT_FAILURE);
}

int	end_heredoc(char *buf, char *bkup, char *filename, int fd)
{
	write(1, "\033[1A", 4);
	write(1, "\033[2C", 4);
	if (bkup)
		write(1, bkup, ft_strlen_js(bkup));
	close(fd);
	unlink(filename);
	free_heredoc(buf, bkup, filename);
	return (EXIT_FAILURE);
}

void	make_bkup(char *buf, char **bkup)
{
	char	*tmp;

	tmp = *bkup;
	*bkup = ft_strjoin_no_free(tmp, buf);
	if (tmp != NULL)
		free(tmp);
	if (buf != NULL)
		free(buf);
}

int	is_file_exist(char *filename, char *buf, char *bkup)
{
	int				tmp_fd;

	tmp_fd = open(filename, O_RDONLY);
	if (tmp_fd < 0)
	{
		ft_putstr_fd("bash: no heredoc file\n", 2);
		free_heredoc(buf, bkup, filename);
		return (EXIT_FAILURE);
	}
	else
		close(tmp_fd);
	return (EXIT_SUCCESS);
}
