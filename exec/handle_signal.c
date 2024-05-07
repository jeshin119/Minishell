/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_signal.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeshin <jeshin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 11:53:53 by jeshin            #+#    #+#             */
/*   Updated: 2024/05/07 16:38:49 by jeshin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	handle_int_to_put_mark(int signum)
{
	write(1, "^C\n", 3);
}

static void	handle_int() // interrupt 시그널 핸들. ctrl+c가 들어왔을 때 처리하는 것
{
	struct termios term;

	tcgetattr(STDIN_FILENO, &term);//stdin 의 속성을 term구조체에 가져와서
	term.c_lflag&= ~(ECHOCTL); // echo속성을 꺼주고
	tcsetattr(STDIN_FILENO, TCSANOW, &term); // 즉시 반영한다.
	write(1, "\n", 1);
	if (rl_on_new_line()) //개행을 출력하고 커서가 한 줄 넘어갔음을 readline쪽에 알려줌.
	{
		perror("rl_on_new_line error");
		exit(EXIT_FAILURE);
	}
	rl_replace_line("", 1);//현재 입력으로 받아 놓은 문자열의 값을 초기화시킴
	rl_redisplay(); //다시 readline실행
}

void	set_signal(struct sigaction *sa_int, struct sigaction *sa_quit) // ctrl+c인 interrupt와 ctrl+d인 quit을 핸들링하는 함수
{
	sigemptyset(&(sa_int->sa_mask)); // sa_int구조체의 mask값을 empty시켜 초기화.
	sa_int->sa_flags = 0; // 마스킹한 값에 대해 추가적으로 어떤 기능을 하지 않을 것이므로 flag=0으로 초기화
	sa_int->sa_handler = handle_int; // handle방법으로 handle_int 전달

	sigemptyset(&(sa_quit->sa_mask));
	sa_quit->sa_flags = 0;
	sa_quit->sa_handler = SIG_IGN;

	//sa_int구조체에 interrupt값을 마스킹하고 핸들링함수를 적용. 여기서 세번째 인자는 이전의 마스킹셋을 담을 수 있는 주소값.
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
