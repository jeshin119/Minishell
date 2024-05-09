/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeshin <jeshin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 17:04:29 by jeshin            #+#    #+#             */
/*   Updated: 2024/05/09 09:48:27 by jeshin           ###   ########.fr       */
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

static int	is_all_space(char *buf)
{
	int		i;

	if (buf == 0)
		return (FALSE);
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

static char	*get_extra_buf(char *buf)
{
	char	*tmp1;
	char	*tmp2;

	while (is_ended_with_pipe(buf))
	{
		tmp1 = readline(">");
		if (tmp1 == 0)
		{
			ft_putstr_fd("bash: syntax error: unexpected end of file\n", 2);
			return (0);
		}
		tmp2 = ft_strjoin_no_free(buf, tmp1);
		free(tmp1);
		free(buf);
		buf = tmp2;
	}
	return (buf);
}

static void	exit_when_eof(void)
{
	write(1, "\033[1A", 4);
	write(1, "\033[10C", 5);
	write(1, "exit\n", 5);
	rl_clear_history();
	exit(EXIT_SUCCESS);
}

char	*check_buf(char *buf, t_dq *env)
{
	char	*ret;

	if (buf == 0)
		exit_when_eof();
	if (*buf == 0 || is_all_space(buf))
	{
		free(buf);
		return (NULL);
	}
	if (*buf == '|')
	{
		ft_putstr_fd("bash: syntax error near unexpected token `|'\n", 2);
		update_prev_status(env, 258);
		return (NULL);
	}
	if (is_ended_with_pipe(buf))
		buf = get_extra_buf(buf);
	if (buf == 0)
		return (NULL);
	if (ft_strlen(buf))
		add_history(buf);
	else
	{
		free(buf);
		return (NULL);
	}
	ret = ft_strdup(buf);
	free(buf);
	return (ret);
}
