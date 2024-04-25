/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeshin <jeshin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 15:21:15 by jeshin            #+#    #+#             */
/*   Updated: 2024/04/24 15:47:46 by jeshin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# define TRUE		1
# define FALSE		0

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include "../libft/libft.h"
# include <sys/wait.h>

typedef struct s_str_ags
{
	int		dq;
	int		sq;
	int		i;
	int		pos;
	int		have_lst_made;
	char	*tmp_s;
}		t_str_ags;

typedef struct s_ags
{
	int		in_f_fd;
	int		out_f_fd;
	int		**pipe_fd_tab;
	int		n_cmd;
	int		idx;
	char	***opts_tab;
	int		is_here_doc;
}		t_ags;

//utils_bonus.c
void	exit_with_errmsg(char *msg);
void	free_tab(char	***tab);
void	free_all(t_ags	*ags);
void	init_str_agr(t_str_ags *chunk);
int		get_mid_substr(char *s, char **ret, int i, int pos);

//init_bonus.c
int		init_ags(t_ags *ags, int ac, char **av);

//path_bonus.c
int		get_opts(char *s, char ***tab);
char	*get_path(char *cmd, char *envp[]);

//pipex_bonus.c
void	my_execve(char **av, int nth, char *envp[]);
void	close_all_pipe(t_ags *ags);
void	go_child(t_ags ags, char **envp);

//main_bonus..c
int	go_pipex(int argc, char *argv[], char *envp[]);

#endif