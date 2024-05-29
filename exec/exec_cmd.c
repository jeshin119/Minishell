/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeshin <jeshin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 14:42:09 by jeshin            #+#    #+#             */
/*   Updated: 2024/05/21 18:01:06 by jeshin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	exec_one_builtin(t_subtree *subtree, t_dq *env)
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
	set_signal_in_exec();
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

static void	link_pipes(t_subtree *subtree, t_tree_info *info, int i)
{
	if (subtree == info->sbt_lst->head)
		my_dup2(subtree, subtree->infile_fd, info->pipe_tab[i][1]);
	else if (subtree == info->sbt_lst->tail)
		my_dup2(subtree, info->pipe_tab[i - 1][0], subtree->outfile_fd);
	else
		my_dup2(subtree, info->pipe_tab[i - 1][0], info->pipe_tab[i][1]);
	close_all_pipe(info->pipe_num, info->pipe_tab);
}

void	exec_multi_cmds(t_subtree *subtree, t_tree_info *info, t_dq *env, int i)
{
	pid_t		child_pid;

	child_pid = fork();
	set_signal_in_exec();
	if (child_pid != 0)
		return ;
	if (is_subtree_ambiguous(subtree) == TRUE)
		exit(EXIT_FAILURE);
	if (has_subtree_no_infile(subtree))
		exit(put_subtree_has_nofile_err_msg(subtree));
	if ((get_infile_fd(subtree)))
		exit(EXIT_FAILURE);
	if (get_outfile_fd(subtree))
		exit(EXIT_FAILURE);
	link_pipes(subtree, info, i);
	if (is_builtin(subtree))
	{
		if (go_builtin(subtree, env) == EXIT_SUCCESS)
			exit(EXIT_SUCCESS);
		exit(EXIT_FAILURE);
	}
	get_path(&(subtree->cmd), env);
	printf("**");
	execve(subtree->cmd, subtree->opt, get_envtab(env));
	exit(EXIT_SUCCESS);
}

void	exec_cmds(t_tree_info *tree_info, t_dq *env)
{
	t_subtree	*subtree;
	int			i;

	subtree = tree_info->sbt_lst->head;
	if (tree_info->pipe_num == 0)
	{
		if (is_builtin(subtree))
			exec_one_builtin(subtree, env);
		else
			exec_one_not_builtin(subtree, env);
		return ;
	}
	i = -1;
	while ((++i < (tree_info->pipe_num + 1)) && subtree)
	{
		if (is_subtree_ambiguous(subtree) == TRUE)
			;
		else
			exec_multi_cmds(subtree, tree_info, env, i);
		subtree = subtree->next;
	}
}
