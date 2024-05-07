/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subtree.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeshin <jeshin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 11:33:29 by jeshin            #+#    #+#             */
/*   Updated: 2024/05/04 11:12:13 by jeshin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	get_file_name(t_tree *tree, t_subtree *subtree)
{
	if (tree == 0 || subtree == 0)
		return (EXIT_FAILURE);
	if (tree->ctrl_token == PIPE)
		return (EXIT_SUCCESS);
	if (tree->ctrl_token == HERE_DOC)
	{
		subtree->is_heredoc = TRUE;
		subtree->infile = get_nth_token_from_lst(tree, tree->tk_idx_set[1]);
	}
	if (tree->ctrl_token == D_RIGHT)
	{
		subtree->is_appending = TRUE;
		subtree->outfile = get_nth_token_from_lst(tree, tree->tk_idx_set[1]);
	}
	if (tree->ctrl_token == LEFT)
		subtree->infile = get_nth_token_from_lst(tree, tree->tk_idx_set[1]);
	if (tree->ctrl_token == RIGHT)
		subtree->outfile = get_nth_token_from_lst(tree, tree->tk_idx_set[1]);
	return (EXIT_SUCCESS);
}

static void	init_subtree(t_subtree **subtree)
{
	*subtree = (t_subtree *)malloc(sizeof(t_subtree));
	if (*subtree == 0)
		exit(ENOMEM);
	(*subtree)->cmd = 0;
	(*subtree)->opt = 0;
	(*subtree)->infile = 0;
	(*subtree)->outfile = 0;
	(*subtree)->infile_fd = 0;
	(*subtree)->outfile_fd = 1;
	(*subtree)->is_heredoc = 0;
	(*subtree)->is_appending = 0;
	(*subtree)->next = 0;
	(*subtree)->prev = 0;
}

static void	link_subtree_to_lst(t_sbt_lst **sbtr_lst, t_subtree *new)
{
	t_sbt_lst *lst;
	t_subtree *here;

	lst = *sbtr_lst;
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
}

static t_subtree *create_subtree(t_tree *tree)
{
	t_tree		*left_child;
	t_tree		*right_child;
	t_subtree	*new;

	init_subtree(&new);
	left_child = tree;
	right_child = tree->next_right;
	while (left_child)
	{
		if (left_child->ctrl_token == 0)
		{
			new->cmd = get_nth_token_from_lst(left_child, (left_child->tk_idx_set)[0]);
			new->opt = get_opt_from_lst(left_child);
			get_file_name(left_child->prev, new);
			break;
		}
		left_child = left_child->next_left;
	}
	while (right_child)
	{
		if(right_child->next_right==0 && right_child->next_right == 0)
		{
			get_file_name(right_child,new);
			break;
		}
		right_child = right_child->next_right;
	}
	return (new);
}

void	make_subtree_lst(t_tree *tree, t_sbt_lst *sbtl)
{
	if (tree->ctrl_token != PIPE)
	{
		link_subtree_to_lst(&sbtl, create_subtree(tree));
	}
	if (tree->ctrl_token == PIPE && tree->next_left && tree->next_right == 0)
	{
		link_subtree_to_lst(&sbtl, create_subtree(tree->next_left));
	}
	if (tree->ctrl_token == PIPE && tree->next_left && tree->next_right)
	{
		link_subtree_to_lst(&sbtl, create_subtree(tree->next_left));
		make_subtree_lst(tree->next_right,sbtl);
	}
	if (tree->ctrl_token == PIPE && tree->next_left == 0 && tree->next_right == 0)
	{
		// char *tmp = readline(NULL);
		// if (ft_strlen(tmp))
		// 	add_history()
		;//cat < qeustion.txt | 이후에 입력을 새로 받음. 새로 wc -l 와 같이 명령주면 합쳐서 실행해야함.
	}
}
