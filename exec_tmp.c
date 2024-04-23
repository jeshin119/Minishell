/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_tmp.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeshin <jeshin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 18:36:38 by jeshin            #+#    #+#             */
/*   Updated: 2024/04/23 12:46:01 by jeshin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

int	my_calloc(void *tab,int bytes, int size)
{
	int	i;
	tab = malloc(sizeof (bytes) * size); //순회할 때 필요한 방문배열을만듦.
	if (tab == 0)
		return (EXIT_FAILURE);
	i = -1;
	while(++i < size) // visted 배열 값 0으로 초기화
		tab[i] = 0;
	return (EXIT_SUCCESS);
}
int	my_malloc(void *tab, int bytes, int size)
{
	tab = malloc(sizeof (int) * size); //순회할 때 필요한 방문배열을만듦.
	if (tab == 0)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

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
	int **pipe_fd_tab;
	if (my_malloc(pipe_fd_tab,4,num))
		return (EXIT_FAILURE);
	int i = -1;
	while (++i < num)
	{
		if (my_malloc(pipe_fd_tab[i], 4, 2))
			return (EXIT_FAILURE);
		if (pipe(pipe_fd_tab[i]))
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

//일단 순서가 파이프 다열고 자식들 커맨드 수만ㄷ큼 만들고 파이프 연결하고 기존 파이프 다 닫고 명령실행.
void	traverse_n_exec(t_tree *tre, t_list *tk_lst, t_dq *env,int *visited) //
{
	if (visited[tre->idx])
		return ;
	if (tre->next_left && tre->next_right == 0) // 왼쪽이 있는데 오른쪽 없으면 왼쪽만들어감.
		traverse_n_exec(tre->next_left, tk_lst, env, visited); 
	if (tre->next_left && tre->next_right)//왼쪽 오른쪽 자식 둘다 있으면 왼쪽 들어가고 오른쪽 들어감.
	{
		traverse_n_exec(tre->next_left, tk_lst, env, visited);
		traverse_n_exec(tre->next_right, tk_lst, env, visited);
	}
	visited[tre->idx] = 1;
	if (tre->pipe) // pipe면 
		return ;
	
	if (exec_bulitin(tk_lst,)){ //bulitin부터 실행하고 
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

//cat <<hi | sleep 3 | ls : heredoc 에 작성한 글 출력안되노..slep3 하고 ls하고 끝남.
//cat <<hi | sleep 3 | wc- l : 결과 : 0
int	go_exec(t_tree *tre, t_list *tk, t_dq *env)
{
	int	**pipe_tab;
	int	pipe_num;
	int *visited;
	int	i;

	if (tre == 0 || tre->end_flag)
		return (EXIT_SUCCESS); //return success ? : tre 에 아무것도 들어오지 않았을 때 echo $? : 0임. 
	pipe_num = get_pipe_num_from_tre; // 파이프 수 구하기.
	pipe_tab = open_pipes(pipe_num); // 파이프 수만큼 파이프를 열어놓음.
	if (pipe_tab) // 오픈 파이프 에러처리.
		return (EXIT_FAILURE);
	if (calloc(visited , pipe_num))
		return (EXIT_FAILURE);
	traverse_n_exec(tre->next_left,tk,env,visited); // 순회하면서 자식을 만들고 명령실행
	return (EXIT_SUCCESS);
}
