/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeshin <jeshin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 15:58:51 by jeshin            #+#    #+#             */
/*   Updated: 2024/05/16 20:49:52 by jeshin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"
#include <sys/stat.h>

void	handle_int_to_exit_heredoc(int signum)
{
	printf("alksdfaklsdfkljkldsjfalk\n");
	if (signum == SIGINT)
	{
		g_status = signum;
		printf("status : %d",g_status);
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

int	main(int argc, char **argv, char **envp)
{
	char	*file;
	struct	stat statbuf;

	file = "a";
	stat(file, &statbuf);
	if (S_ISREG(statbuf.st_mode) == 0)
	{
		ft_putstr_fd("bash: ",2);
		ft_putstr_fd(file,2);
		ft_putstr_fd(": ",2);
		perror(NULL);
		g_status = ENOENT;
	}
	return (EXIT_FAILURE);
}	