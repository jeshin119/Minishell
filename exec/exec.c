/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeshin <jeshin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 18:36:38 by jeshin            #+#    #+#             */
/*   Updated: 2024/05/08 12:53:45 by jeshin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	exec_one_not_builtins(t_subtree *subtree, t_dq *env)
{
	char	*path;

	signal(SIGINT, SIG_DFL);
	path = get_path(subtree->cmd, env);
	redirection(subtree, 0, 0);
	execve(path, subtree->opt, get_envtab(env));
}

static void	exec_builtins(t_subtree *subtree, t_dq *env)
{
	int		stdin_copy;
	int		stdout_copy;
	char	*path;

	signal(SIGINT, SIG_DFL);
	redirection(subtree, &stdin_copy, &stdout_copy);
	g_status = go_builtins(subtree, env);
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

void	exec_multi_cmds(t_subtree *subtree, t_tree_info *info, t_dq *env, int i)
{
	pid_t		child_pid;

	child_pid = fork();
	if (child_pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		subtree->infile_fd = get_infile_fd(subtree);
		subtree->outfile_fd = get_outfile_fd(subtree);
		if (subtree == info->sbt_lst->head)
			my_dup2(subtree, subtree->infile_fd, info->pipe_tab[i][1]);
		else if (subtree == info->sbt_lst->tail)
			my_dup2(subtree, info->pipe_tab[i - 1][0], subtree->outfile_fd);
		else
			my_dup2(subtree, info->pipe_tab[i - 1][0], info->pipe_tab[i][1]);
		close_all_pipe(info->pipe_num, info->pipe_tab);
		if (go_builtins(subtree, env) == EXIT_SUCCESS)
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
			exec_builtins(subtree, env);
		else
		{
			child_pid = fork();
			if (child_pid == 0)
				exec_one_not_builtins(subtree, env);
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

int	exec_tree(t_tree *tree, t_dq *env)
{
	t_tree_info	tree_info;
	int			i;

	init_tree_info(tree, &tree_info);
	if (make_subtree_lst(tree, tree_info.sbt_lst, env))
		return (EXIT_FAILURE);
	signal(SIGINT, handle_int_to_put_mark);
	exec_subtree(tree, &tree_info, env);
	close_all_pipe(tree_info.pipe_num, tree_info.pipe_tab);
	i = -1;
	while (++i < tree_info.pipe_num + 1)
	{
		waitpid(-1, &g_status, 0);
		if (WIFEXITED(g_status))
			update_prev_status(env, WEXITSTATUS(g_status));
		else if (WIFSIGNALED(g_status))
			update_prev_status(env, WTERMSIG(g_status) + 128);
	}
	reset_tree_info(&tree_info);
	return (EXIT_SUCCESS);
}
