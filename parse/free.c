/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeshin <jeshin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 19:14:25 by seunghan          #+#    #+#             */
/*   Updated: 2024/05/07 15:14:42 by jeshin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	free_tk_list(t_list *tk_list)
{
	t_list	*last_node;
	int		i;

	i = 0;
	if (!tk_list)
		return ;
	while (tk_list)
	{
		if (tk_list -> token)
			free(tk_list -> token);
		if (tk_list -> env_lset)
			free(tk_list -> env_lset);
		if (tk_list -> prev)
			free(tk_list -> prev);
		if (!tk_list -> next)
			last_node = tk_list;
		tk_list = tk_list -> next;
	}
	free(last_node);
}

static void	free_left_tree(t_tree *tree)
{
	tree = free_sub_tree(tree);
	free(tree -> next_left);
}

static void	free_right_tree(t_tree *tree)
{
	while (tree -> next_right)
		tree = tree -> next_right;
	while (tree -> prev)
	{
		free_next_node(tree);
		tree = go_to_subroot(tree);
		tree = free_sub_tree(tree);
		if (!tree -> next_left && tree -> prev)
			tree = tree -> prev;
	}
	free(tree -> next_right);
}

void	free_all(t_tree *tree, t_list *tk_list)
{
	go_to_first(&tree, &tk_list);
	free_tk_list(tk_list);
	if (tree && tree -> next_left)
		free_left_tree(tree);
	if (tree && tree -> next_right)
		free_right_tree(tree);
	if (tree)
	{
		free_tk_idx_set(tree);
		free(tree);
	}
}
