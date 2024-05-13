/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeshin <jeshin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 18:36:38 by jeshin            #+#    #+#             */
/*   Updated: 2024/05/13 11:55:15 by jeshin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	exec_builtin(t_subtree *subtree, t_dq *env)
{
	int		stdin_copy;
	int		stdout_copy;

	if (b_redirection(subtree, &stdin_copy, &stdout_copy))
	{
		g_status = 1;
		return ;
	}
	g_status = go_builtin(subtree, env);
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

static void	exec_one_not_builtin(t_subtree *subtree, t_dq *env)
{
	int		stdin_copy;
	int		stdout_copy;
	pid_t	child_pid;

	child_pid = fork();
	if (child_pid == 0)
	{
		get_path(&(subtree->cmd), env);
		redirection(subtree, &stdin_copy, &stdout_copy);
		execve(subtree->cmd, subtree->opt, get_envtab(env));
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
		exit(EXIT_SUCCESS);
	}
}

static void	exec_cmds(t_subtree *subtree, t_tree_info *info, t_dq *env, int i)
{
	pid_t		child_pid;

	child_pid = fork();
	if (child_pid == 0)
	{
		subtree->infile_fd = get_infile_fd(subtree);
		subtree->outfile_fd = get_outfile_fd(subtree);
		if (subtree == info->sbt_lst->head)
			my_dup2(subtree, subtree->infile_fd, info->pipe_tab[i][1]);
		else if (subtree == info->sbt_lst->tail)
			my_dup2(subtree, info->pipe_tab[i - 1][0], subtree->outfile_fd);
		else
			my_dup2(subtree, info->pipe_tab[i - 1][0], info->pipe_tab[i][1]);
		close_all_pipe(info->pipe_num, info->pipe_tab);
		if (is_builtin(subtree))
		{
			if (go_builtin(subtree, env) == EXIT_SUCCESS)
				exit(EXIT_SUCCESS);
			exit(EXIT_FAILURE);
		}
		get_path(&(subtree->cmd), env);
		execve(subtree->cmd, subtree->opt, get_envtab(env));
	}
}

static void	exec_sbtr(t_tree_info *tree_info, t_dq *env)
{
	t_subtree	*subtree;
	int			i;

	subtree = tree_info->sbt_lst->head;
	if (tree_info->pipe_num == 0)
	{
		if (is_builtin(subtree))
			exec_builtin(subtree, env);
		else
			exec_one_not_builtin(subtree, env);
	}
	else
	{
		i = -1;
		while (++i < tree_info->pipe_num + 1)
		{
			exec_cmds(subtree, tree_info, env, i);
			subtree = subtree->next;
		}
	}
}

int	exec_tree(t_tree *tree, t_dq *env)
{
	t_tree_info	tree_info;

	init_tree_info(tree, &tree_info);
	open_pipes(tree_info.pipe_num, &(tree_info.pipe_tab));
	if (make_subtree_lst(tree, &tree_info, env))
	{
		reset_tree_info(&tree_info);
		return (EXIT_FAILURE);
	}
	signal(SIGINT, handle_int_to_put_mark);
	exec_sbtr(&tree_info, env);
	close_all_pipe(tree_info.pipe_num, tree_info.pipe_tab);
	wait_childs(&tree_info, env);
	reset_tree_info(&tree_info);
	return (EXIT_SUCCESS);
}
