/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeshin <jeshin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 18:36:38 by jeshin            #+#    #+#             */
/*   Updated: 2024/05/02 17:17:00 by jeshin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

static void	my_dup2(int rd, int wr)
{
	if (rd != STDIN_FILENO){
		if (dup2(rd, 0) < 0)
			perror("dup2 error");
	}
	if (wr != STDOUT_FILENO){
		if (dup2(wr, 1) < 0)
			perror("dup2 error");
	}
}

int	exec_builtins(t_subtree *subtree,t_dq *env)
{
	if (subtree->cmd == 0)
		return (EXIT_FAILURE);
	if (!ft_strncmp(subtree->cmd, "echo", 5))
		_echo(subtree);
	else if(!ft_strncmp(subtree->cmd, "cd", 3))
		_cd(subtree->cmd,env);
	else if(!ft_strncmp(subtree->cmd, "pwd", 4))
		_pwd();
	else if(!ft_strncmp(subtree->cmd, "export", 7))
		_export((subtree->opt)[0],(subtree->opt)[1],env);
	else if(!ft_strncmp(subtree->cmd, "unset", 6))
		_unset(env,(subtree->opt)[1]);
	else if(!ft_strncmp(subtree->cmd, "env", 4))
		_env(env);
	else if(!ft_strncmp(subtree->cmd, "exit", 5))
		_exit_();
	else
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

static void exec_subtree(t_tree *tree ,t_tree_info *tree_info,t_dq *env)
{
	pid_t		child_pid;
	t_sbt_lst	*sbt_lst;
	t_subtree	*subtree;
	int			i;

	subtree = tree_info->sbt_lst->head;
	if (tree_info->pipe_num == 0)
	{
		child_pid = fork();
		if (child_pid == 0)
		{
			signal(SIGINT,SIG_DFL);
			subtree->infile_fd = get_infile_fd(subtree);
			subtree->outfile_fd = get_outfile_fd(subtree);
			if (subtree->infile_fd != STDIN_FILENO)
				my_dup2(subtree->infile_fd, STDOUT_FILENO);
			if (subtree->outfile_fd != STDOUT_FILENO)
				my_dup2(subtree->infile_fd, STDOUT_FILENO);
			if (exec_builtins(subtree, env))
				execve(get_path(subtree->cmd,env) ,subtree->opt, get_envtab(env));
		}
	}
	else{
		i=-1;
		while (++i < tree_info->pipe_num + 1)
		{
			child_pid = fork();
			if (child_pid == 0)
			{
				signal(SIGINT,SIG_DFL);
				subtree->infile_fd = get_infile_fd(subtree);
				subtree->outfile_fd = get_outfile_fd(subtree);
				if (subtree == tree_info->sbt_lst->head)
					my_dup2(subtree->infile_fd, tree_info->pipe_tab[i][1]);
				else if (subtree == tree_info->sbt_lst->tail)
					my_dup2(tree_info->pipe_tab[i - 1][0],subtree->outfile_fd);
				else
					my_dup2(tree_info->pipe_tab[i - 1][0], tree_info->pipe_tab[i][1]);
				close_all_pipe(tree_info->pipe_num, tree_info->pipe_tab);
				if (exec_builtins(subtree, env))
					execve(get_path(subtree->cmd, env) ,subtree->opt, get_envtab(env));
			}
			subtree = subtree->next;
		}
	}
}

void exec_tree(t_tree *tree, t_dq *env)
{
	t_tree_info	tree_info;
	int state;

	init_tree_info(tree , &tree_info);
	make_subtree_lst(tree, tree_info.sbt_lst);
	exec_subtree(tree , &tree_info, env);
	close_all_pipe(tree_info.pipe_num, tree_info.pipe_tab);
	for(int i=0;i<tree_info.pipe_num + 1;i++)
	{
		signal(SIGINT, SIG_IGN);
		waitpid(-1, &state, 0);
	}
	reset_tree_info(&tree_info);
}
