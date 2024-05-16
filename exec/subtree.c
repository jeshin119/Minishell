/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subtree.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeshin <jeshin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 09:22:35 by jeshin            #+#    #+#             */
/*   Updated: 2024/05/16 18:55:52 by jeshin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	init_subtree(t_subtree **subtree)
{
	*subtree = (t_subtree *)malloc(sizeof(t_subtree));
	if (*subtree == 0)
	{
		perror("malloc: ");
		exit(EXIT_FAILURE);
	}
	(*subtree)->cmd = 0;
	(*subtree)->opt = 0;
	(*subtree)->opt_size = 0;
	(*subtree)->infile = 0;
	(*subtree)->outfile = 0;
	(*subtree)->infile_fd = 0;
	(*subtree)->outfile_fd = 1;
	(*subtree)->is_heredoc = 0;
	(*subtree)->is_appending = 0;
	(*subtree)->is_ambiguous = 0;
	(*subtree)->next = 0;
	(*subtree)->prev = 0;
}

static int	get_cmd_opt(t_tree *tree, t_subtree *new, t_dq *env)
{
	if (tree == 0)
		return (EXIT_FAILURE);
	if (tree->ctrl_token != 0)
		return (get_cmd_opt(tree->next_left, new, env));
	if (tree->exit_code == 258)
	{
		put_errmsg_syntax_err(tree);
		g_status = 258;
		update_prev_status(env);
		return (EXIT_FAILURE);
	}
	env_chk(tree, env->head);
	new->cmd = get_nth_token_from_lst(tree, (tree->tk_idx_set)[0]);
	if (new->cmd == 0)
		return (EXIT_FAILURE);
	get_opt_from_lst(tree, &new);
	return (EXIT_SUCCESS);
}

static t_subtree	*create_subtree(t_tree *tree, t_dq *env)
{
	t_subtree	*new;

	init_subtree(&new);
	if (tree->exit_code == 258)
	{
		put_errmsg_syntax_err(tree);
		free(new);
		g_status = 258;
		update_prev_status(env);
		return (NULL);
	}
	if (get_cmd_opt(tree, new, env))
	{
		new->is_ambiguous = 1;
		return (new);
	}
	if (is_file_err(tree, new, env, get_infile(tree, new, env)))
		return (NULL);
	if (is_file_err(tree, new, env, get_outfile(tree, new, env)))
		return (NULL);
	return (new);
}

static int	link_subtree_to_lst(t_sbt_lst **sbtr_lst, t_subtree *new)
{
	t_sbt_lst	*lst;
	t_subtree	*here;

	lst = *sbtr_lst;
	if (new == 0)
		return (EXIT_FAILURE);
	if (lst->head == 0)
	{
		lst->head = new;
		lst->tail = new;
		new->next = 0;
		new->prev = 0;
	}
	else
	{
		here = lst->head;
		while (here->next)
			here = here->next;
		here->next = new;
		new->prev = here;
		new->next = 0;
		lst->tail = new;
	}
	return (EXIT_SUCCESS);
}

int	make_subtree_lst(t_tree *tree, t_tree_info *info, t_dq *env)
{
	t_subtree	*new;
	t_sbt_lst	*sbtl;

	sbtl = info->sbt_lst;
	if (g_status == SIGINT)
		return (EXIT_FAILURE);
	if (tree->ctrl_token != PIPE)
	{
		new = create_subtree(tree, env);
		return (link_subtree_to_lst(&sbtl, new));
	}
	if (tree->ctrl_token == PIPE && tree->next_left && tree->next_right == 0)
	{
		new = create_subtree(tree->next_left, env);
		return (link_subtree_to_lst(&sbtl, new));
	}
	if (tree->ctrl_token == PIPE && tree->next_left && tree->next_right)
	{
		new = create_subtree(tree->next_left, env);
		return (link_subtree_to_lst(&sbtl, new) | \
		make_subtree_lst(tree->next_right, info, env));
	}
	return (EXIT_FAILURE);
}
