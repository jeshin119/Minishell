/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_signal.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeshin <jeshin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 11:53:53 by jeshin            #+#    #+#             */
/*   Updated: 2024/05/16 16:01:02 by jeshin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	handle_int_to_put_mark(int signum)
{
	if (WIFSIGNALED(signum))
		g_status = WTERMSIG(g_status) + 128;
	ioctl(STDIN_FILENO, TIOCSTI, "\n");
}

void	handle_int_to_exit_heredoc(int signum)
{
	if (signum == SIGINT)
	{
		g_status = signum;
		ioctl(STDIN_FILENO, TIOCSTI, "\n");
		write(1, "\033[1A", 4);
	}
}

void	handle_int_in_main(int signum)
{
	struct termios	term;

	if (WIFSIGNALED(signum))
		g_status = 1;
	tcgetattr(STDIN_FILENO, &term);
	term.c_lflag &= ~(ECHOCTL);
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 1);
	rl_redisplay();
}

void	set_main_signal(void)
{
	t_sig	sig;

	sigemptyset(&(sig.sa_int.sa_mask));
	sig.sa_int.sa_flags = 0;
	sig.sa_int.sa_handler = handle_int_in_main;
	sigemptyset(&(sig.sa_quit.sa_mask));
	sig.sa_quit.sa_flags = 0;
	sig.sa_quit.sa_handler = SIG_IGN;
	if (sigaction(SIGINT, &(sig.sa_int), NULL) == -1)
		perror("sigaction: ");
	if (sigaction(SIGQUIT, &(sig.sa_quit), NULL) == -1)
		perror("sigaction: ");
}

void	handle_sigint_to_rl_restart(int signum)
{
	if (signum == SIGINT)
	{
		g_status = signum;
		ioctl(STDIN_FILENO, TIOCSTI, "\n");
		write(1, "\033[1A", 4);
	}
}
