/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeshin <jeshin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 17:04:29 by jeshin            #+#    #+#             */
/*   Updated: 2024/05/20 18:11:00 by jeshin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

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

int	check_extra_buf(char **bkup, char **buf)
{
	int		heredoc_is;
	char	*tmp;

	if (g_status == SIGINT)
	{
		free(*buf);
		return (EXIT_FAILURE);
	}
	if (*buf == 0)
	{
		ft_putstr_fd("bash: syntax error: unexpected end of file\n", 2);
		return (EXIT_FAILURE);
	}
	heredoc_is = 0;
	tmp = ft_strjoin_no_free(*bkup, *buf);
	add_history(tmp);
	free(*bkup);
	*bkup = tmp;
	if (check_buf_syntax_err(*buf, &heredoc_is) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	tmp = ft_strdup(*buf);
	free(*buf);
	*buf = tmp;
	return (EXIT_SUCCESS);
}
