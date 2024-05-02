/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeshin <jeshin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 18:36:38 by jeshin            #+#    #+#             */
/*   Updated: 2024/05/03 10:35:47 by jeshin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

static void	my_dup2(t_subtree *subtree, int rd, int wr)
{
	if (subtree->infile_fd == STDIN_FILENO && rd != STDIN_FILENO)
	{
		if (dup2(rd, 0) < 0)
			perror("dup2: ");
	}
	if (subtree->infile_fd != STDIN_FILENO)
	{
		if (dup2(subtree->infile_fd, 0) < 0)
			perror("dup2: ");
	}
	if (subtree->outfile_fd == STDOUT_FILENO && wr != STDOUT_FILENO)
	{
		if (dup2(wr, 1) < 0)
			perror("dup2: ");
	}
	if (subtree->outfile_fd != STDOUT_FILENO)
	{
		if (dup2(subtree->outfile_fd, 1) < 0)
			perror("dup2: ");
	}
}

int	exec_builtins(t_subtree *subtree,t_dq *env)
{
	if (subtree->cmd == 0)
		return (EXIT_FAILURE);
	if (!ft_strncmp(subtree->cmd, "echo", 5))
		return (_echo(subtree));
	else if(!ft_strncmp(subtree->cmd, "cd", 3))
		return (_cd(subtree->cmd,env));
	else if(!ft_strncmp(subtree->cmd, "pwd", 4))
		return (_pwd());
	else if(!ft_strncmp(subtree->cmd, "export", 7))
		return (_export((subtree->opt)[0],(subtree->opt)[1],env));
	else if(!ft_strncmp(subtree->cmd, "unset", 6))
		return (_unset(env,(subtree->opt)[1]));
	else if(!ft_strncmp(subtree->cmd, "env", 4))
		return (_env(env));
	else if(!ft_strncmp(subtree->cmd, "exit", 5))
		return (_exit_());
	else
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	is_builtins(t_subtree *subtree)
{
	if (subtree->cmd == 0)
		return (FALSE);
	if (!ft_strncmp(subtree->cmd, "echo", 5))
		return (TRUE);
	else if(!ft_strncmp(subtree->cmd, "cd", 3))
		return (TRUE);
	else if(!ft_strncmp(subtree->cmd, "pwd", 4))
		return (TRUE);
	else if(!ft_strncmp(subtree->cmd, "export", 7))
		return (TRUE);
	else if(!ft_strncmp(subtree->cmd, "unset", 6))
		return (TRUE);
	else if(!ft_strncmp(subtree->cmd, "env", 4))
		return (TRUE);
	else if(!ft_strncmp(subtree->cmd, "exit", 5))
		return (TRUE);
	else
		return (FALSE);
	return (TRUE);
}

void	exec_when_one_cmd(){

}

static void exec_subtree(t_tree *tree, t_tree_info *tree_info, t_dq *env)
{
	pid_t		child_pid;
	t_subtree	*subtree;
	int			i;

	subtree = tree_info->sbt_lst->head;
	if (tree_info->pipe_num == 0)
	{
		if (is_builtins(subtree))
		{
			signal(SIGINT, SIG_DFL);
			subtree->infile_fd = get_infile_fd(subtree);
			subtree->outfile_fd = get_outfile_fd(subtree);
			if (subtree->infile_fd != STDIN_FILENO)
				my_dup2(subtree, subtree->infile_fd, STDOUT_FILENO);
			if (subtree->outfile_fd != STDOUT_FILENO)
				my_dup2(subtree ,subtree->infile_fd, STDOUT_FILENO);
			exec_builtins(subtree, env);
		}
		else
		{
			child_pid = fork();
			if (child_pid == 0)
			{
				signal(SIGINT,SIG_DFL);
				subtree->infile_fd = get_infile_fd(subtree);
				subtree->outfile_fd = get_outfile_fd(subtree);
				if (subtree->infile_fd != STDIN_FILENO)
					my_dup2(subtree, subtree->infile_fd, STDOUT_FILENO);
				if (subtree->outfile_fd != STDOUT_FILENO)
					my_dup2(subtree, subtree->infile_fd, STDOUT_FILENO);
				else
					execve(get_path(subtree->cmd,env) ,subtree->opt, get_envtab(env));
			}
		}
	}
	else
	{
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
					my_dup2(subtree, subtree->infile_fd, tree_info->pipe_tab[i][1]);
				else if (subtree == tree_info->sbt_lst->tail)
					my_dup2(subtree, tree_info->pipe_tab[i - 1][0],subtree->outfile_fd);
				else
					my_dup2(subtree, tree_info->pipe_tab[i - 1][0], tree_info->pipe_tab[i][1]);
				close_all_pipe(tree_info->pipe_num, tree_info->pipe_tab);
				if (exec_builtins(subtree, env) == EXIT_SUCCESS)
					exit(EXIT_SUCCESS);
				else
					execve(get_path(subtree->cmd, env) ,subtree->opt, get_envtab(env));
			}
			subtree = subtree->next;
		}
	}
}

static void	handle_int_to_put_mark(int signum)
{
	write(1, "^C\n", 1);
}

void exec_tree(t_tree *tree, t_dq *env)
{
	t_tree_info	tree_info;
	int state;

	init_tree_info(tree , &tree_info);
	make_subtree_lst(tree, tree_info.sbt_lst);
	exec_subtree(tree , &tree_info, env);
	close_all_pipe(tree_info.pipe_num, tree_info.pipe_tab);
	signal(SIGINT, handle_int_to_put_mark);
	for(int i=0;i<tree_info.pipe_num + 1;i++)
		waitpid(-1, &state, 0);
	reset_tree_info(&tree_info);
}
