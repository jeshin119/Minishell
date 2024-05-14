/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeshin <jeshin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 17:04:29 by jeshin            #+#    #+#             */
/*   Updated: 2024/05/14 18:51:56 by jeshin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	is_ended_with_pipe(char *buf)
{
	int		i;
	char	*here;

	if (buf == 0)
		return (FALSE);
	here = ft_strrchr(buf, '|');
	if (here == NULL)
		return (FALSE);
	i = ft_strlen(buf);
	while (--i)
	{
		if (ft_isspace(buf[i]))
			continue ;
		if (&(buf[i]) > here)
			return (FALSE);
	}
	return (TRUE);
}

static int	is_empty(char *buf)
{
	int		i;

	if (*buf == 0)
		return (TRUE);
	i = -1;
	while (buf[++i])
	{
		if (ft_isspace(buf[i]))
			continue ;
		if (buf[i])
			return (FALSE);
	}
	return (TRUE);
}

static int	get_extra_buf(char **buf)
{
	char	*extra;

	signal(SIGINT, handle_sigint_to_rl_restart);
	while (is_ended_with_pipe(*buf))
	{
		extra = readline("> ");
		if (g_status == SIGINT)
		{
			add_history(*buf);
			free(*buf);
			g_status = 1;
			return (EXIT_FAILURE);
		}
		if (extra == 0)
		{
			add_history(*buf);
			free(*buf);
			g_status = 258;
			write(1, "\033[1A\033[2C", 8);
			ft_putstr_fd("bash: syntax error: unexpected end of file\n", 2);
			return (EXIT_FAILURE);
		}
		*buf = ft_strjoin(*buf, extra);
	}
	return (EXIT_SUCCESS);
}

static void	exit_when_eof(void)
{
	write(1, "\033[1A", 4);
	write(1, "\033[10C", 5);
	write(1, "exit\n", 5);
	rl_clear_history();
	exit(EXIT_SUCCESS);
}

int	check_buf(char **buf, t_dq *env)
{
	char	*tmp;

	if (*buf == 0)
		exit_when_eof();
	if (is_empty(*buf))
		return (EXIT_FAILURE);
	if (check_syntax_err(*buf))
	{
		update_prev_status(env);
		return (EXIT_FAILURE);
	}
	if (get_extra_buf(buf))
	{
		update_prev_status(env);
		return (EXIT_FAILURE);
	}
	add_history(*buf);
	tmp = ft_strdup(*buf);
	free(*buf);
	*buf = tmp;
	return (EXIT_SUCCESS);
}
