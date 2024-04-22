/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeshin <jeshin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 18:01:09 by jeshin            #+#    #+#             */
/*   Updated: 2024/04/22 15:30:55 by jeshin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex_bonus.h"

void	my_execve(char **av, int nth, char *envp[])
{
	char	*path;
	char	**opts;

	if (get_opts(av[nth], &opts) == -1)
		exit_with_errmsg("opts error");
	path = get_path(opts[0], envp);
	if (path == 0)
		exit_with_errmsg("path error");
	execve(path, opts, envp);
}

static void	my_dup2(int rd, int wr)
{
	if (dup2(rd, 0) < 0)
		perror("dup2 error");
	if (dup2(wr, 1) < 0)
		perror("dup2 error");
}

void	close_all_pipe(t_ags *ags)
{
	int	i;

	i = -1;
	while (++i < ags->n_cmd -1)
	{
		close(ags->pipe_fd_tab[i][0]);
		close(ags->pipe_fd_tab[i][1]);
	}
}

void	go_child(t_ags ags, char **envp)
{
	pid_t	child_pid;
	char	**opts;

	child_pid = fork();
	if (child_pid == 0)
	{
		if (ags.idx == 0)
			my_dup2(ags.in_f_fd, ags.pipe_fd_tab[ags.idx][1]);
		else if (ags.idx + 1 == ags.n_cmd)
			my_dup2(ags.pipe_fd_tab[ags.idx - 1][0], ags.out_f_fd);
		else
			my_dup2(ags.pipe_fd_tab[ags.idx - 1][0] \
			, ags.pipe_fd_tab[ags.idx][1]);
		close_all_pipe(&ags);
		opts = ags.opts_tab[ags.idx];
		execve(get_path(opts[0], envp), opts, envp);
		perror("execve error");
	}
}
