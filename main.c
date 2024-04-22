/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeshin <jeshin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 12:56:23 by jeshin            #+#    #+#             */
/*   Updated: 2024/04/22 18:59:50 by jeshin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

void check_leak()
{
	system("leaks a.out");
}
void handle_int() // interrupt 시그널 핸들. ctrl+c가 들어왔을 때 처리하는 것
{
	struct termios term;
	tcgetattr(STDIN_FILENO, &term);//stdin 의 속성을 term구조체에 가져와서
	term.c_lflag&= ~(ECHOCTL); // echo속성을 꺼주고
	tcsetattr(STDIN_FILENO, TCSANOW, &term); // 즉시 반영한다.
	write(1,"\n",1);
	if (rl_on_new_line()) //개행을 출력하고 커서가 한 줄 넘어갔음을 readline쪽에 알려줌.
	{
		perror("rl_on_new_line error");
		exit(EXIT_FAILURE);
	}
	rl_replace_line("",1);//현재 입력으로 받아 놓은 문자열의 값을 초기화시킴
	rl_redisplay(); //다시 readline실행
}

int set_signal(struct sigaction *sa_int, struct sigaction *sa_quit) // ctrl+c인 interrupt와 ctrl+d인 quit을 핸들링하는 함수
{
	sigemptyset(&(sa_int->sa_mask)); // sa_int구조체의 mask값을 empty시켜 초기화.
	sa_int->sa_flags = 0; // 마스킹한 값에 대해 추가적으로 어떤 기능을 하지 않을 것이므로 flag=0으로 초기화
	sa_int->sa_handler = handle_int; // handle방법으로 handle_int 전달

	sigemptyset(&(sa_quit->sa_mask));
	sa_quit->sa_flags = 0;
	sa_quit->sa_handler = SIG_IGN;

	//sa_int구조체에 interrupt값을 마스킹하고 핸들링함수를 적용. 여기서 세번째 인자는 이전의 마스킹셋을 담을 수 있는 주소값.
	if (sigaction(SIGINT, sa_int, NULL)==-1) 
	{ 
		perror("sigaction error");
		return (EXIT_FAILURE);
	}
	if (sigaction(SIGQUIT, sa_quit, NULL)==-1)
	{
		perror("sigaction error");
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

static void	put_exit_when_eof(void)
{
	write(1,"\033[1A",4);
	write(1,"\033[10C",5);
	write(1,"exit\n",5);
	rl_clear_history();
	exit(EXIT_SUCCESS);
}
static void	mke_my_env(char **e, t_dq *env)
{
	char	**tmp;

	init_dq(env);
	while (*e)
	{
		tmp = ft_split(*e, '=');
		push_back_dq(env, tmp[0], tmp[1]);
		free(tmp);
		e++;
	}
}

int main(int ac, char **av, char **envp){
	t_sig sig;
	char *buf;
	t_dq *env;
	t_tree	*tre;
	t_list	*tk;
	if (set_signal(&(sig.sa_int),&(sig.sa_quit))) //시그널 처리
		return (EXIT_FAILURE);
	// bash-3.2$에서 -이후 숫자가 bash버전임. 버전가져와야함.안가져와도 되나? ㅋㅋ
	// int version = get_bash_version(envp);
	mke_my_env(envp, env);
	while(TRUE)
	{
		buf = readline("bash-3.2$ ");
		if (buf == 0) //ctrl+d로 eof가 들어오면 
			put_exit_when_eof();
		if (ft_strlen(buf)) //노드 헤드가 있다면 history에 추가 
			add_history(buf);// 방향키로 이전에 입력한 커맨드 불러올 수 있음.
		tk = tokenize(buf); //사용할 때 이렇게 사용하면 되는지?
		tre = make_tree(tre,tk,env);
		go_exec(tre,env);
		free(buf);
	}
	return (EXIT_SUCCESS);
}