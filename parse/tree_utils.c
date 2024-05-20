/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeshin <jeshin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 13:20:03 by seunghan          #+#    #+#             */
/*   Updated: 2024/05/20 11:53:09 by seunghan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_tree	*go_to_pipe(t_tree *now)
{
	if (!now)
		return (0);
	while (now -> prev)
	{
		if (now -> ctrl_token == PIPE)
			return (now);
		now = now -> prev;
	}
	return (now);
}

t_tree	*go_to_subroot(t_tree *now)
{
	if (!now)
		return (0);
	while (now -> prev)
	{
		if (now -> prev -> ctrl_token == PIPE)
			return (now);
		now = now -> prev;
	}
	return (now);
}

t_tree	*syntax_error_malloc(t_tree *now, t_list *tk_list, int meta_value)
{
	if (meta_value == PIPE)
	{
		if (!now)
			now = malloc_tree_node(now, tk_list, NO_DR);
		else
			now = malloc_tree_node(now, tk_list, RIGHT);
	}
	else if (meta_value >= LEFT && meta_value <= D_RIGHT)
	{
		if (tk_list -> next)
			(now -> tk_idx_set)[1] = tk_list -> next -> token_idx;
		else
			(now -> tk_idx_set)[1] = END;
	}
	now -> exit_code = 258;
	return (now);
}

static char	*malloc_readline(char *buf)
{
	int		i;
	char	*buf_m;

	i = 0;
	while (buf[i])
		i++;
	buf_m = (char *)malloc(i + 1);
	if (!buf_m)
		exit(1);
	i = 0;
	while (buf[i])
	{
		buf_m[i] = buf[i];
		i++;
	}
	buf_m[i] = 0;
	free(buf);
	return (buf_m);
}

t_tree	*add_pipe_input(t_tree *now, t_list *tk_list)
{
	int		i;
	char	*buf;
	t_list	*tk_list_add;

	if (!now || !tk_list)
		return (0);
	i = 0;
	if (now -> ctrl_token == PIPE && !(now -> next_right))
	{
		buf = readline("> ");
		buf = malloc_readline(buf);
		tk_list_add = tokenize(buf, ADD);
		now = make_tree(now, tk_list_add);
		while (tk_list -> next)
			tk_list = tk_list -> next;
		tk_list -> next = tk_list_add;
		tk_list_add -> prev = tk_list;
		free(buf);
	}
	return (now);
}
