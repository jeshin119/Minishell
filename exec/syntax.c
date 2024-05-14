/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeshin <jeshin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 17:23:34 by jeshin            #+#    #+#             */
/*   Updated: 2024/05/14 18:51:35 by jeshin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	put_err_msg(char *s, int idx)
{
	ft_putstr_fd("bash: syntax error near unexpected token `", 2);
	if (s[idx])
		write(2, &s[idx], 1);
	else
		write(2, "newline", 7);
	ft_putstr_fd("'\n", 2);
	free(s);
	g_status = 258;
	return (EXIT_FAILURE);
}

static void	init(char *s, int i, int *deli, int *depth)
{
	int		k;
	char	*set;

	set = "<|>";
	k = -1;
	while (set[++k])
	{
		if (set[k] == s[i])
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

	set = "<|>";
	k = i;
	init (s, i, &deli, &depth);
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

static int	check(char *s, int i, int *status)
{
	int	ret;

	ret = 0;
	if (s[i] == '<' || s[i] == '>')
	{
		ret = check_behind(i, s);
		if (ret)
		{
			*status = ret;
			return (EXIT_FAILURE);
		}
	}
	return (EXIT_SUCCESS);
}

int	check_syntax_err(char *s)
{
	int	i;
	int	sq;
	int	dq;
	int	status;

	sq = FALSE;
	dq = FALSE;
	if (*s == '|')
		return (EXIT_FAILURE);
	if (s == 0)
		return (EXIT_SUCCESS);
	i = -1;
	while (s[++i])
	{
		if (s[i] == '\'' && dq == FALSE)
			sq = !sq;
		if (s[i] == '"' && sq == FALSE)
			dq = !dq;
		if (sq == FALSE && dq == FALSE)
		{
			if (check(s, i, &status))
				return (put_err_msg(s, status));
		}
	}
	return (EXIT_SUCCESS);
}
