/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jeshin.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeshin <jeshin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 12:56:23 by jeshin            #+#    #+#             */
/*   Updated: 2024/04/17 17:39:23 by jeshin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

// int	exec_bulitin(char *cmd,char *option)
// {
// 	if (cmd == 0)
// 		return (EXIT_FAILURE);
// 	if (!ft_strncmp(cmd, "echo", 5))
// 		_echo();
// 	else if(!ft_strncmp(cmd, "cd", 3))
// 		_cd();
// 	else if(!ft_strncmp(cmd, "pwd", 4))
// 		_pwd();
// 	else if(!ft_strncmp(cmd, "export", 7))
// 		_export();
// 	else if(!ft_strncmp(cmd, "unset", 6))
// 		_unset();
// 	else if(!ft_strncmp(cmd, "env", 4))
// 		_env();
// 	else if(!ft_strncmp(cmd, "exit", 5))
// 		_exit_();
// 	else
// 		return (EXIT_FAILURE);
// 	return (EXIT_SUCCESS);
// }

// int	go_exec(int ac, char *av[], char *env[])
// {
// 	//순회하면서 커맨드 실행
// 	//bulit in commands
// 	if (exec_bulitin())
// 	//not bulit in commands
// 	t_ags	ags;
// 	int		status;
// 	int		i;

// 	init_ags(&ags, ac, av);
// 	while (++(ags.idx) < ags.n_cmd)
// 		go_child(ags, env);
// 	close_all_pipe(&ags);
// 	i = -1;
// 	while (++i < ags.n_cmd)
// 		waitpid(-1, &status, 0);
// 	close(ags.in_f_fd);
// 	close(ags.out_f_fd);
// 	free_all(&ags);
// 	return (0);
// }

void	put_exit_when_eof(void)
{
	write(1,"\033[1A",4);
	write(1,"\033[10C",5);
	write(1,"exit\n",5);
	rl_clear_history();
	exit(EXIT_SUCCESS);
}

int main(int ac, char **av, char **envp){
	t_sh sh;
	char *buf;

	if (set_signal(&(sh.sa_int),&(sh.sa_quit))) //시그널 처리
		return (EXIT_FAILURE);

	// bash-3.2$에서 -이후 숫자가 bash버전임. 버전가져와야함.안가져와도 되나? ㅋㅋ
	// int version = get_bash_version(envp);

	while(TRUE)
	{
		buf = readline("bash-3.2$ ");
		if (buf == 0) //ctrl+d로 eof가 들어오면 
			put_exit_when_eof();
		if (ft_strlen(buf)) //노드 헤드가 있다면 history에 추가 
			add_history(buf);// 방향키로 이전에 입력한 커맨드 불러올 수 있음.
		// parse(); 
		// const int SIZE=3;
		// char *tmp[3] = {"echo","-n",NULL};
		go_exec(ac,av,envp);
		free(buf);
	}
	return (EXIT_SUCCESS);
}