/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeshin <jeshin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 18:36:38 by jeshin            #+#    #+#             */
/*   Updated: 2024/05/17 20:30:13 by jeshin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	exec_builtin(t_subtree *subtree, t_dq *env)
{
	int		stdin_copy;
	int		stdout_copy;

	if (is_subtree_ambiguous(subtree) == TRUE)
		return (EXIT_FAILURE);
	if (redirection(subtree, &stdin_copy, &stdout_copy))
		return (EXIT_FAILURE);
	g_status = go_builtin(subtree, env);
	get_back_redirection(subtree, stdin_copy, stdout_copy);
	return (EXIT_SUCCESS);
}

static void	exec_one_not_builtin(t_subtree *subtree, t_dq *env)
{
	int		stdin_copy;
	int		stdout_copy;
	pid_t	child_pid;

	child_pid = fork();
	if (child_pid != 0)
		return ;
	if (is_subtree_ambiguous(subtree) == TRUE)
		exit(EXIT_FAILURE);
	if (redirection(subtree, &stdin_copy, &stdout_copy))
		exit(EXIT_FAILURE);
	get_path(&(subtree->cmd), env);
	execve(subtree->cmd, subtree->opt, get_envtab(env));
	get_back_redirection(subtree, stdin_copy, stdout_copy);
	exit(EXIT_SUCCESS);
}

static void	exec_cmds(t_subtree *subtree, t_tree_info *info, t_dq *env, int i)
{
	pid_t		child_pid;

	child_pid = fork();
	if (child_pid != 0)
		return ;
	if (is_subtree_ambiguous(subtree) == TRUE)
		exit(EXIT_FAILURE);
	if (has_subtree_no_infile(subtree))
	{
		put_subtree_has_nofile_err_msg(subtree);
		g_status = 1;
		exit(EXIT_FAILURE);
	}
	if ((get_infile_fd(subtree)))
		exit(EXIT_FAILURE);
	if (get_outfile_fd(subtree))
		exit(EXIT_FAILURE);
	if (get_path(&(subtree->cmd), env))
		exit(127);
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
	execve(subtree->cmd, subtree->opt, get_envtab(env));
	exit(EXIT_FAILURE);
}

static void	go_exec(t_tree_info *tree_info, t_dq *env)
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
		return ;
	}
	i = -1;
	while (++i < tree_info->pipe_num + 1)
	{
		if (is_subtree_ambiguous(subtree) == TRUE)
			;
		else
			exec_cmds(subtree, tree_info, env, i);
		subtree = subtree->next;
	}
}

int	exec_tree(t_tree *tree, t_dq *env)
{
	t_tree_info	tree_info;

	init_tree_info(tree, &tree_info);
	if (mke_subtree_lst(tree, &tree_info, env) == EXIT_FAILURE)
	{
		reset_tree_info(&tree_info);
		return (EXIT_FAILURE);
	}
	open_pipes((tree_info.pipe_num), &(tree_info.pipe_tab));
	signal(SIGINT, handle_int_to_put_mark);
	signal(SIGQUIT, SIG_DFL);
	go_exec(&tree_info, env);
	close_all_pipe(tree_info.pipe_num, tree_info.pipe_tab);
	wait_childs(&tree_info, env);
	reset_tree_info(&tree_info);
	return (EXIT_SUCCESS);
}
