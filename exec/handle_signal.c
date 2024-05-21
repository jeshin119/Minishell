/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_signal.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeshin <jeshin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 11:53:53 by jeshin            #+#    #+#             */
/*   Updated: 2024/05/21 13:30:56 by jeshin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	handle_sigint_in_main(int signum)
{
	if (WIFSIGNALED(signum))
		g_status = SIGINT;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 1);
	rl_redisplay();
}

void	handle_sigint_to_exit_readline(int signum)
{
	struct termios	term;

	if (signum == SIGINT)
	{
		tcgetattr(STDOUT_FILENO, &term);
		term.c_lflag &= ~(ECHOCTL);
		tcsetattr(STDOUT_FILENO, TCSANOW, &term);
		g_status = SIGINT;
		ioctl(STDIN_FILENO, TIOCSTI, "\n");
		write(1, "\033[1A", 4);
	}
}

void	set_signal_in_main(void)
{
	struct termios		term;
	struct sigaction	sa_int;
	struct sigaction	sa_quit;

	tcgetattr(STDOUT_FILENO, &term);
	term.c_lflag &= ~(ECHOCTL);
	tcsetattr(STDOUT_FILENO, TCSANOW, &term);
	sigemptyset(&(sa_int.sa_mask));
	sa_int.sa_flags = 0;
	sa_int.sa_handler = handle_sigint_in_main;
	sigemptyset(&(sa_quit.sa_mask));
	sa_quit.sa_flags = 0;
	sa_quit.sa_handler = SIG_IGN;
	if (sigaction(SIGINT, &(sa_int), NULL) == -1)
		perror("sigaction: ");
	if (sigaction(SIGQUIT, &(sa_quit), NULL) == -1)
		perror("sigaction: ");
}

static void	handle_sigint_sigquit_to_kill_processes(int signum)
{
	if (signum == SIGINT)
	{
		g_status = 128 + SIGINT;
		write(2, "\n", 1);
		kill (-2, SIGINT);
	}
	if (signum == SIGQUIT)
	{
		g_status = 128 + SIGQUIT;
		write(2, "QUIT: 3\n", 8);
		kill (-2, SIGQUIT);
	}
}

void	set_signal_in_exec(void)
{
	struct termios	term;

	tcgetattr(STDOUT_FILENO, &term);
	term.c_lflag |= (ECHOCTL);
	tcsetattr(STDOUT_FILENO, TCSANOW, &term);
	signal(SIGINT, handle_sigint_sigquit_to_kill_processes);
	signal(SIGQUIT, handle_sigint_sigquit_to_kill_processes);
}
