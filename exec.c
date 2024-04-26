/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeshin <jeshin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 18:36:38 by jeshin            #+#    #+#             */
/*   Updated: 2024/04/26 18:18:51 by jeshin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

int	exec_builtins(t_subtree *subtree,t_dq *env)
{
	if (subtree->cmd == 0)
		return (EXIT_FAILURE);
	if (!ft_strncmp(subtree->cmd, "echo", 5))
		_echo(subtree->opt,subtree->cmd);
	else if(!ft_strncmp(subtree->cmd, "cd", 3))
		_cd(subtree->cmd,env);
	else if(!ft_strncmp(subtree->cmd, "pwd", 4))
		_pwd();
	else if(!ft_strncmp(subtree->cmd, "export", 7))
		_export((subtree->opt)[0],(subtree->opt)[1],env);
	else if(!ft_strncmp(subtree->cmd, "unset", 6))
		_unset(env,subtree->opt);
	else if(!ft_strncmp(subtree->cmd, "env", 4))
		_env(env);
	else if(!ft_strncmp(subtree->cmd, "exit", 5))
		_exit_();
	else
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

char	*get_path(char *cmd, t_dq *env)
{
	t_node *start=env->head;
	char *path;
	while(start){
		if (ft_strncmp(start->name,"PATH",4)==0)
			break;
		start=start->next;
	}
	char **tab = ft_split(start->val, ':');
	int i=-1;
	while(tab[++i]){
		char *tmp = ft_strjoin_no_free(tab[i],"/");
		free(tab[i]);
		tab[i] = tmp;
	}
	i=-1;
	while(tab[++i]){
		path = ft_strjoin_no_free(tab[i],cmd);
		if (access(path, F_OK | X_OK) == 0)
		{
			free_tab(tab);
			return (path);
		}
		free(path);
	}
	free_tab(tab);
	perror("path error");
	exit(127);
	return (NULL);
}


int exec_not_builtin(char *cmd, char **opt, t_dq *env)
{
}

//마지x막 노드가 |로 끝나면 추가로 입력받아서 처리해야함//이건 나중에 처리합시다 
void	close_all_pipe(int size, int **pipe_tab)
{
	int	i;

	i = -1;
	while (++i < size)
	{
		close(pipe_tab[i][0]);
		close(pipe_tab[i][1]);
	}
}

void exec(t_tree_info *tree_info,t_dq *env)
{
	pid_t		child_pid;
	t_sbt_lst	*sbt_lst;
	t_subtree	*subtree;
	int			i;

	subtree = tree_info->sbt_lst->head;
	if (tree_info->pipe_num == 0)
	{
		if (exec_builtins(subtree, env))
			execve(get_path(subtree->cmd,env) ,subtree->opt, env);
	}
	i=-1;
	while(++i<tree_info->pipe_num)
	{
		child_pid = fork();
		if (child_pid == 0)
		{
			if (subtree == tree_info->sbt_lst->head)
				my_dup2(subtree->infile_fd, tree_info->pipe_tab[i][1]);
			else if (subtree == tree_info->sbt_lst->tail)
				my_dup2(tree_info->pipe_tab[i-1][0],subtree->outfile_fd);
			else
				my_dup2(tree_info->pipe_tab[i - 1][0], tree_info->pipe_tab[i][1]);
			close_all_pipe(tree_info->pipe_num, tree_info->pipe_tab);
			execve(get_path(subtree->cmd,env) ,subtree->opt, env);
			perror("execve error");
		}
		subtree = subtree->next;
	}
	wait(NULL);
}
