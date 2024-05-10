/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_signal.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeshin <jeshin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 11:53:53 by jeshin            #+#    #+#             */
/*   Updated: 2024/05/10 12:52:23 by jeshin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	handle_int_to_put_mark(int sign)
{
	sign = 1;
	write(1, "^C\n", 3);
}

static void	handle_int(int n)
{
	struct termios	term;

	n = 1;
	tcgetattr(STDIN_FILENO, &term);
	term.c_lflag &= ~(ECHOCTL);
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
	write(1, "\n", 1);
	if (rl_on_new_line())
	{
		perror("rl_on_new_line error");
		exit(EXIT_FAILURE);
	}
	rl_replace_line("", 1);
	rl_redisplay();
}

void	set_signal(struct sigaction *sa_int, struct sigaction *sa_quit)
{
	sigemptyset(&(sa_int->sa_mask));
	sa_int->sa_flags = 0;
	sa_int->sa_handler = handle_int;
	sigemptyset(&(sa_quit->sa_mask));
	sa_quit->sa_flags = 0;
	sa_quit->sa_handler = SIG_IGN;
	if (sigaction(SIGINT, sa_int, NULL) == -1)
	{
		perror("sigaction error: ");
		exit (EXIT_FAILURE);
	}
	if (sigaction(SIGQUIT, sa_quit, NULL) == -1)
	{
		perror("sigaction error: ");
		exit (EXIT_FAILURE);
	}
}
