/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subtree.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeshin <jeshin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 14:41:27 by jeshin            #+#    #+#             */
/*   Updated: 2024/05/08 14:41:28 by jeshin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	open_write_heredoc(t_subtree *subtree)
{
	char	*buf;
	char	*limiter;
	int		size_of_limiter;
	int		heredoc_fd;
	char	*filename;

	if (subtree == 0)
		return (EXIT_FAILURE);
	limiter = subtree->infile;
	if (limiter == 0)
		return (EXIT_FAILURE);
	filename = ft_strjoin_no_free(".here_doc_", limiter);
	heredoc_fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (heredoc_fd < 0)
		perror_n_exit("heredoc");
	size_of_limiter = ft_strlen(limiter);
	while (TRUE)
	{
		buf = readline("> ");
		if (buf == 0 || ft_strncmp(buf, limiter, size_of_limiter + 1) == 0)
			break ;
		if (write(heredoc_fd, buf, ft_strlen(buf) + 1) < 0)
			return (EXIT_FAILURE);
		if (write(heredoc_fd, "\n", 1) < 0)
			return (EXIT_FAILURE);
		free(buf);
	}
	if (buf != NULL)
		free(buf);
	close(heredoc_fd);
	subtree->infile = filename;
	return (heredoc_fd);
}

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
		subtree->infile_fd = open_write_heredoc(subtree);
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

static int	link_subtree_to_lst(t_sbt_lst **sbtr_lst, t_subtree *new)
{
	t_sbt_lst *lst;
	t_subtree *here;

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

void put_errmsg_syntax_err(t_tree *tree)
{
	printf("bash: syntax error near unexpected token ");
	if (tree->tk_list -> ctrl_token == PIPE)
		printf("'|'\n");
	else if (tree->tk_list -> prev && tree->tk_list -> prev -> ctrl_token)
		printf("'%s'\n", tree->tk_list -> token);
	else if (tree->tk_list -> next)
		printf("'%s'\n", tree->tk_list -> next -> token);
	else
		printf("'newline'\n");
}

static t_subtree *create_subtree(t_tree *tree, t_dq *env)
{
	t_tree		*left_child;
	t_tree		*right_child;
	t_subtree	*new;

	init_subtree(&new);
	left_child = tree;
	right_child = tree->next_right;
	if (tree->exit_code == 258)
	{
		put_errmsg_syntax_err(tree);
		return (NULL);
	}
	while (left_child)
	{
		if (left_child->ctrl_token == 0)
		{
			env_chk(left_child, env->head);
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
			env_chk(right_child, env->head);
			get_file_name(right_child, new);
			break;
		}
		right_child = right_child->next_right;
	}
	return (new);
}

int	make_subtree_lst(t_tree *tree, t_sbt_lst *sbtl, t_dq *env)
{
	t_subtree	*new;

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
		return (link_subtree_to_lst(&sbtl, new) & \
		make_subtree_lst(tree->next_right, sbtl, env));
	}
	if (tree->ctrl_token == PIPE && \
	tree->next_left == 0 && tree->next_right == 0)
	{
		put_errmsg_syntax_err(tree);
		return (EXIT_FAILURE);
	}
	return (EXIT_FAILURE);
}
