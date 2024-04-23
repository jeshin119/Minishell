/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeshin <jeshin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 15:15:38 by jeshin            #+#    #+#             */
/*   Updated: 2024/04/23 09:47:46 by jeshin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex_bonus.h"
#include "../include/minishell.h"
#include "../include/minishell.h"

static int	care_here_doc(int ac, char **av, t_ags *ags)
{
	int		size_lim;
	char	*buf;
	int		tmp_fd;

	ags->is_here_doc = 1;
	tmp_fd = open(".here_doc_tmp_f", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (tmp_fd < 0)
		return (-1);
	size_lim = ft_strlen(av[2]);
	while (TRUE)
	{
		buf = get_next_line(0);
		if (ft_strncmp(buf, av[2], size_lim) == 0)
			break ;
		if (write(tmp_fd, buf, ft_strlen(buf)) < 0)
			return (-1);
		free(buf);
	}
	free(buf);
	close((tmp_fd));
	ags->in_f_fd = open(".here_doc_tmp_f", O_RDONLY);
	ags->out_f_fd = open(av[ac - 1], O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (ags->out_f_fd < 0)
		exit_with_errmsg("open outfile error");
	return (0);
}

static int	care_opts_tab(t_ags *ags, int ac, char **av)
{
	int	i;

	ags->n_cmd = ac -3 - ags->is_here_doc;
	ags->opts_tab = (char ***)malloc(sizeof(char **) * (ags->n_cmd + 1));
	if (ags->opts_tab == 0)
		return (-1);
	(ags->opts_tab)[ags->n_cmd] = 0;
	i = -1;
	while (++i < (ags->n_cmd))
	{
		if (get_opts(av[i + 2 + ags->is_here_doc], &((ags->opts_tab)[i])) == -1)
		{
			free(ags->opts_tab);
			return (-1);
		}
	}
	return (0);
}

static int	make_pipe_tab(t_ags *ags)
{
	int	i;

	ags->pipe_fd_tab = (int **)malloc(sizeof(int *) * (ags->n_cmd -1));
	if (ags->pipe_fd_tab == 0)
		return (-1);
	i = -1;
	while (++i < (ags->n_cmd -1))
	{
		ags->pipe_fd_tab[i] = (int *)malloc(sizeof(int) * 2);
		if (ags->pipe_fd_tab[i] == 0)
			return (-1);
		if (pipe(ags->pipe_fd_tab[i]))
			return (-1);
	}
	return (0);
}


int	init_ags(t_ags *ags, int ac, char **av)
{
	if (ac < 5)
		exit_with_errmsg("argc error");
	if (ft_strncmp(av[1], "here_doc", 9) == 0)
	{
		if (care_here_doc(ac, av, ags) == -1)
			exit_with_errmsg("here_doc error");
	}
	else
	{
		ags->is_here_doc = 0;
		ags->in_f_fd = open(av[1], O_RDONLY);
		if (ags->in_f_fd < 0)
			exit_with_errmsg("open infile error");
		ags->out_f_fd = open(av[ac - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (ags->out_f_fd < 0)
			exit_with_errmsg("open outfile error");
	}
	ags->idx = -1;
	if (care_opts_tab(ags, ac, av) == -1)
		exit_with_errmsg("opts error");
	if (make_pipe_tab(ags) == -1)
		exit_with_errmsg("pipe_tab error");
	return (0);
}
