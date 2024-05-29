/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeshin <jeshin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 17:23:34 by jeshin            #+#    #+#             */
/*   Updated: 2024/05/17 15:53:03 by jeshin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	init(char c, char **set, int *deli, int *depth)
{
	int		k;

	*set = "<|>";
	k = -1;
	while ((*set)[++k])
	{
		if ((*set)[k] == c)
			*deli = k;
	}
	*depth = 0;
}

static int	check_behind(int i, char *s)
{
	int		k;
	int		depth;
	int		deli;
	char	*set;

	init (s[i], &set, &deli, &depth);
	k = i;
	while (s[++k])
	{
		if (ft_isspace(s[k]))
			continue ;
		if (ft_isalnum(s[k]))
			return (EXIT_SUCCESS);
		if (depth == 0 && \
		(s[k] == set[(deli + 1) % 3] || s[k] == set[(deli + 2) % 3]))
			return (k);
		depth++;
	}
	if (depth == 0)
		return (k);
	return (EXIT_SUCCESS);
}

int	is_heredoc(int *i, char *s)
{
	int	d;
	int	j;

	if (*i == 0 || (size_t)(*i) == ft_strlen(s))
		return (FALSE);
	d = 0;
	j = (*i)--;
	while (s[++(*i)])
	{
		if (s[(*i)] == '<' && s[(*i) + 1] == '<')
		{
			d++;
			continue ;
		}
		if (d && ft_isalnum(s[(*i)]))
			return (TRUE);
		if (d && (s[(*i)] == '|' || s[(*i)] == '>'))
		{
			*i = j;
			return (FALSE);
		}
	}
	*i = j;
	return (FALSE);
}

static int	check(char *s, int i, int *status, int *heredoc)
{
	int	ret;

	ret = 0;
	*status = 0;
	if (s[i] == '<' || s[i] == '>')
	{
		ret = check_behind(i, s);
		if (is_heredoc(&i, s))
		{
			*heredoc = 1;
			return (EXIT_FAILURE);
		}
		if (ret)
		{
			*status = ret;
			return (EXIT_FAILURE);
		}
	}
	return (EXIT_SUCCESS);
}

int	check_buf_syntax_err(char *s, int *heredoc)
{
	int	i;
	int	sq;
	int	dq;
	int	status;

	sq = FALSE;
	dq = FALSE;
	status = 0;
	if (*s == '|')
		return (put_buf_has_syntax_err_msg(s, status, *heredoc));
	i = -1;
	while (s[++i])
	{
		if (s[i] == '\'' && dq == FALSE)
			sq = !sq;
		if (s[i] == '"' && sq == FALSE)
			dq = !dq;
		if (sq == FALSE && dq == FALSE)
		{
			if (check(s, i, &status, heredoc))
				return (put_buf_has_syntax_err_msg(s, status, *heredoc));
		}
	}
	return (EXIT_SUCCESS);
}
