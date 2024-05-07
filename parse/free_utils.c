/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeshin <jeshin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 12:18:13 by seunghan          #+#    #+#             */
/*   Updated: 2024/05/07 15:14:36 by jeshin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	go_to_first(t_tree **tree, t_list **tk_list)
{
	if (*tk_list)
	{
		while ((*tk_list)-> prev)
			*tk_list = (*tk_list)-> prev;
	}
	if (*tree)
	{
		while ((*tree)-> prev)
			*tree = (*tree)-> prev;
	}
}

void	free_tk_idx_set(t_tree *tree)
{
	if (tree -> tk_idx_set)
	{
		free(tree -> tk_idx_set);
		tree -> tk_idx_set = 0;
	}
}

void	free_next_node(t_tree *tree)
{
	if (!tree -> prev)
		return ;
	if (tree -> next_left)
	{
		if (!tree -> next_left -> tk_idx_set)
		{
			free(tree -> next_left);
			tree -> next_left = 0;
		}
	}
	if (tree -> next_right)
	{
		if (!tree -> next_right -> tk_idx_set)
		{
			free(tree -> next_right);
			tree -> next_right = 0;
		}
	}
}

t_tree	*free_sub_tree(t_tree *tree)
{
	while (tree -> next_left)
		tree = tree -> next_left;
	while (tree -> prev && tree -> ctrl_token != PIPE)
	{
		free_tk_idx_set(tree);
		if (tree -> next_right)
		{
			while (tree -> next_right)
				tree = tree -> next_right;
			while (tree -> prev && tree -> prev -> ctrl_token != PIPE)
			{
				free_tk_idx_set(tree);
				free_next_node(tree);
				tree = tree -> prev;
			}
		}
		free_next_node(tree);
		if (tree -> prev)
			tree = tree -> prev;
	}
	return (tree);
}
