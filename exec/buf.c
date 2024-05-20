/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeshin <jeshin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 17:04:29 by jeshin            #+#    #+#             */
/*   Updated: 2024/05/20 15:13:42 by jeshin           ###   ########.fr       */
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
	{
		free(buf);
		return (TRUE);
	}
	i = -1;
	while (buf[++i])
	{
		if (ft_isspace(buf[i]))
			continue ;
		if (buf[i])
			return (FALSE);
	}
	add_history(buf);
	free(buf);
	buf = 0;
	return (TRUE);
}

static int	get_extra_buf(char **buf)
{
	char	*extra;

	if (is_ended_with_pipe(*buf) == FALSE)
		return (EXIT_SUCCESS);
	extra = readline("> ");
	if (g_status == SIGINT)
	{
		if (extra)
			free(extra);
		add_history(*buf);
		free(*buf);
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
	return (get_extra_buf(buf));
}

static int	exit_when_eof(void)
{
	write(1, "\033[1A", 4);
	write(1, "\033[10C", 5);
	write(1, "exit\n", 5);
	rl_clear_history();
	return (EXIT_SUCCESS);
}

int	check_buf(char **buf)
{
	char	*tmp;
	int		heredoc;

	if (*buf == 0 && (exit_when_eof() == EXIT_SUCCESS))
		exit(EXIT_SUCCESS);
	if (is_empty(*buf))
		return (EXIT_FAILURE);
	heredoc = 0;
	if (check_buf_syntax_err(*buf, &heredoc) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	signal(SIGINT, handle_sigint_to_exit_readline);
	if (!heredoc && get_extra_buf(buf))
	{
		signal(SIGINT, handle_sigint_in_main);
		return (EXIT_FAILURE);
	}
	signal(SIGINT, handle_sigint_in_main);
	add_history(*buf);
	tmp = ft_strdup(*buf);
	free(*buf);
	*buf = tmp;
	return (EXIT_SUCCESS);
}

int	check_extra_buf(char *prev, char **buf)
{
	char	*tmp;
	int		heredoc;

	if (*buf == 0)
		exit_when_eof();
	if (is_empty(*buf))
		return (EXIT_FAILURE);
	heredoc = 0;
	if (check_buf_syntax_err(*buf, &heredoc) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	tmp = ft_strjoin_no_free(prev, *buf);
	add_history(tmp);
	free(tmp);
	return (EXIT_SUCCESS);
}
