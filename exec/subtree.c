/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subtree.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeshin <jeshin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 09:22:35 by jeshin            #+#    #+#             */
/*   Updated: 2024/05/29 16:41:51 by jeshin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	init_subtree(t_subtree **subtree)
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
	(*subtree)->no_infile = 0;
	(*subtree)->outfile = 0;
	(*subtree)->infile_fd = 0;
	(*subtree)->outfile_fd = 1;
	(*subtree)->is_heredoc = 0;
	(*subtree)->is_appending = 0;
	(*subtree)->is_ambiguous = 0;
	(*subtree)->next = 0;
	(*subtree)->prev = 0;
}

int	create_subtree(t_tree *tree, t_subtree **new, t_dq *env)
{
	init_subtree(new);
	if (check_subtree_syntax_err(tree, new))
		return (free_subtree(new));
	if (get_infile(tree, new, env))
		return (free_subtree(new));
	if (get_cmd_opt(tree, new))
		return (free_subtree(new));
	if (get_outfile(tree, new))
		return (free_subtree(new));
	return (EXIT_SUCCESS);
}

int	link_subtree(t_sbt_lst **sbtr_lst, t_subtree *new)
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
