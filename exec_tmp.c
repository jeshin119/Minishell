/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_tmp.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeshin <jeshin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 18:36:38 by jeshin            #+#    #+#             */
/*   Updated: 2024/04/23 09:47:19 by jeshin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"
//temporary//
int	exec_builtins(char *cmd, char **opt, t_dq *env)
{
	if (cmd == 0)
		return (EXIT_FAILURE);
	if (!ft_strncmp(cmd, "echo", 5))
		_echo(opt,cmd);
	else if(!ft_strncmp(cmd, "cd", 3))
		_cd(cmd,env);
	else if(!ft_strncmp(cmd, "pwd", 4))
		_pwd();
	else if(!ft_strncmp(cmd, "export", 7))
		_export(opt[0],opt[1],env);
	else if(!ft_strncmp(cmd, "unset", 6))
		_unset(env,opt);
	else if(!ft_strncmp(cmd, "env", 4))
		_env(env);
	else if(!ft_strncmp(cmd, "exit", 5))
		_exit_();
	else
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int exec_not_builtin(char *cmd, char **opt, t_dq *env)
{
	t_ags	ags;
	int		status;
	int		i;

	init_ags(&ags, ac, av);
	while (++(ags.idx) < ags.n_cmd)
		go_child(ags, env);
	close_all_pipe(&ags);
	i = -1;
	while (++i < ags.n_cmd)
		waitpid(-1, &status, 0);
	close(ags.in_f_fd);
	close(ags.out_f_fd);
	free_all(&ags);
}

int get_pipe_num_from_tre(t_tree *tre)
{
	int	n;

	n = 0;
	while(tre)
	{
		if (tre == pipe)
			n++;
		tre=tre->next_right;
	}
	return (n);
}

int	**open_pipes(int num)
{
	int **pipe_fd_tab = (int **)malloc(sizeof(int *) * num);
	if (pipe_fd_tab == 0)
		return (EXIT_FAILURE);
	int i = -1;
	while (++i < num)
	{
		pipe_fd_tab[i] = (int *)malloc(sizeof(int) * 2);
		if (pipe_fd_tab[i] == 0)
			return (EXIT_FAILURE);
		if (pipe(pipe_fd_tab[i]))
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int	traverse_n_exec(t_tree *tre, t_list *tk, t_dq *env)
{
	if (tre == 0 || tre->end_flag)
		return (EXIT_SUCCESS);
	while (tre->end_flag == 0)
	{
		

	}
	if (exec_bulitin()){ //bulitin부터 실행하고 
		if (exec_not_builtin()) //bultin아니면 파일에서 실행하고
			return (EXIT_FAILURE); //그것도 아니면 뭔가 이상.
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

int	go_exec(t_tree *tre, t_list *tk, t_dq *env)
{
	int	**pipe_tab;
	int	pipe_num;
	int	i;

	if (tre == 0 || tre->end_flag)
		return (EXIT_SUCCESS); //tre 에 아무것도 들어오지 않았을 때 echo $? : 0임. 
	pipe_num = get_pipe_num_from_tre;
	pipe_tab = open_pipes(pipe_num); // 파이프 수만큼 파이프를 열어놓음.
	if (pipe_tab) // 오픈 파이프 에러처리.
		return (EXIT_FAILURE);
	traverse_n_exec(tre->next_left,tk,env); // 순회하면서 자식을 만들고 명령실행
	return (EXIT_SUCCESS);
}
