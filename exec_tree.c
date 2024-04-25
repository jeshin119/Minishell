/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_tree.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeshin <jeshin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 18:36:38 by jeshin            #+#    #+#             */
/*   Updated: 2024/04/24 17:19:55 by jeshin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"


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

//마지막 노드가 |로 끝나면 추가로 입력받아서 처리해야함//이건 나중에 처리합시다 
void ex(t_tree *tre)
{
	if (tre->ctrl_token == PIPE || tre->ctrl_token == HERE_DOC \
	||tre->ctrl_token == LEFT || tre->ctrl_token == RIGHT || tre->ctrl_token == D_RIGHT)
		return ;
	//자식을 어디서 만들어야 되노?
	if (exec_bulitin()){ //bulitin부터 실행하고 
		if (exec_not_builtin()) //bultin아니면 파일에서 실행하고
			return (EXIT_FAILURE); //그것도 아니면 뭔가 이상.
	}

}

//먼저 순회하면서 파이프연결하고 히어독 받도록 하려했는데 그러면 안됨.아니네 그래도 되네. 
// echo hi|sleep 2 | cat<<end 하니까 입력먼저 받고 이초 쉬고 끝남. hi는 출력안됨.
// sleep 2|echo hi|wc-l| cat<<end 하니까 히어독먼저 입력받고 wc-l가 명령이 아니라고 뜸.
// sleep 2|echo hi|wc -l| cat<<end 라고 제대로 입력해도 입력먼저받고 wc -l결과는 출력안됨.
//echo hi|wc -l|sleep 3 도 마찬가지. 3초쉬고 그냥 끝남.
//결론 : 먼저 히어독 받고. 먼저 연결하고 그담에 실행한다. 

//pipex에서는 어케했지? 자식 뿌리고 자식에서 파이프연결하고 명령어 실행하고. 부모는 모든파이프 닫고 자식하나하나 기다리고
//여기선 어케하면되지? 트리 순회하면서 다 연결? 트리순회하다가 파이프만나면 파이프 왼쪽 자식만들고 파이프오른쪽 자식만들고 

void	*fork_link_exec(t_tree * tree)
{
	pid_t	child_pid;

	child_pid=fork();
	if (child_pid == 0) // 자식이면
	{
	}
}

//일단 순서가 파이프 다열고 자식들 커맨드 수만ㄷ큼 만들고 파이프 연결하고 기존 파이프 다 닫고 명령실행.
void	traverse_tree(t_tree *tree, t_dq *env, int *visited)
{
	if (visited[tree->idx])//visited가 필요한가..?visited없으면 어떻게 되나? 없어도 될거 같은디?
		return ;
	if (tree->next_left && tree->next_right == 0) // 왼쪽이 있는데 오른쪽 없으면 왼쪽만들어감.
	{
		traverse_n_exec(tree->next_left, env, visited); 
		visited[tree->idx] = 1;
		fork_link_exec(tree);
	}
	if (tree->next_left && tree->next_right)//왼쪽 오른쪽 자식 둘다 있으면 왼쪽 들어가고 오른쪽 들어감.
	{
		traverse_n_exec(tree->next_left, env, visited);
		visited[tree->idx] = 1;
		fork_link_exec(tree);
		traverse_n_exec(tree->next_right, env, visited);
	}
	else {
		visited[tree->idx] = 1;
		fork_link_exec(tree);
	}
}

//cat <<hi | sleep 3 | ls : heredoc 에 작성한 글 출력안되노..slep3 하고 ls하고 끝남.
//cat <<hi | sleep 3 | wc- l : 결과 : 0
int	go_exec(t_tree *tree, t_list *tk, t_dq *env)
{
	int	pipe_num;
	int *visited;
	int	i;

	if (tree == 0 || tree->end_flag)
		return (EXIT_SUCCESS); //return success ? : tre 에 아무것도 들어오지 않았을 때 echo $? : 0임. 

	visited = (int *)malloc(sizeof (4) * pipe_num); //순회할 때 필요한 방문배열을만듦. // 방문배열필요한가? 인접리스트가 아니라 세방향 연결리스트인디?//나중에 고려.
	if (visited == 0)
		return (EXIT_FAILURE);
	i = -1;
	while(++i < pipe_num) // visted 배열 값 0으로 초기화
		visited[i] = 0;

	traverse_tree(tree, env, visited); 
	//close_all_pipe,,
	// wait(NULL);
	return (EXIT_SUCCESS);
}
