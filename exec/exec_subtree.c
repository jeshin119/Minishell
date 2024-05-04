/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_subtree.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeshin <jeshin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 11:02:07 by jeshin            #+#    #+#             */
/*   Updated: 2024/05/07 11:12:21 by jeshin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	exec_one_cmd(t_subtree *subtree, t_tree_info *tree_info, t_dq *env, int is_builtin)
{
	int stdin_copy;
	int stdout_copy;

	signal(SIGINT, SIG_DFL);
	subtree->infile_fd = get_infile_fd(subtree);
	subtree->outfile_fd = get_outfile_fd(subtree);
	if (subtree->infile_fd != STDIN_FILENO || subtree->outfile_fd != STDOUT_FILENO)
	{
		stdin_copy = dup(STDIN_FILENO);
		stdout_copy = dup(STDOUT_FILENO);
		my_dup2(subtree, subtree->infile_fd, subtree->outfile_fd);
	}
	if (is_builtin)
	{
		exec_builtins(subtree, env);
		if (subtree->infile_fd != STDIN_FILENO)
		{
			dup2(stdin_copy, STDIN_FILENO);
			close(subtree->infile_fd);
		}
		if (subtree->outfile_fd != STDOUT_FILENO)
		{
			dup2(stdout_copy, STDOUT_FILENO);
			close(subtree->outfile_fd);
		}
	}
	else
	{
		execve(get_path(subtree->cmd, env), subtree->opt, get_envtab(env));
	}
}

static void	exec_multi_cmds(t_subtree *subtree, t_tree_info *tree_info, t_dq *env, int i)
{
	pid_t		child_pid;

	child_pid = fork();
	if (child_pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		subtree->infile_fd = get_infile_fd(subtree);
		subtree->outfile_fd = get_outfile_fd(subtree);
		if (subtree == tree_info->sbt_lst->head)
			my_dup2(subtree, subtree->infile_fd, tree_info->pipe_tab[i][1]);
		else if (subtree == tree_info->sbt_lst->tail)
			my_dup2(subtree, tree_info->pipe_tab[i - 1][0], subtree->outfile_fd);
		else
			my_dup2(subtree, tree_info->pipe_tab[i - 1][0], tree_info->pipe_tab[i][1]);
		close_all_pipe(tree_info->pipe_num, tree_info->pipe_tab);
		if (exec_builtins(subtree, env) == EXIT_SUCCESS)
			exit(EXIT_SUCCESS);
		else
			execve(get_path(subtree->cmd, env), subtree->opt, get_envtab(env));
	}
}

void	exec_subtree(t_tree *tree, t_tree_info *tree_info, t_dq *env)
{
	pid_t		child_pid;
	t_subtree	*subtree;
	int			i;

	subtree = tree_info->sbt_lst->head;
	if (tree_info->pipe_num == 0)
	{
		if (is_builtins(subtree))
			exec_one_cmd(subtree, tree_info, env, 1);
		else
		{
			child_pid = fork();
			if (child_pid == 0)
				exec_one_cmd(subtree, tree_info, env, 0);
		}
	}
	else
	{
		i = -1;
		while (++i < tree_info->pipe_num + 1)
		{
			exec_multi_cmds(subtree, tree_info, env, i);
			subtree = subtree->next;
		}
	}
}
