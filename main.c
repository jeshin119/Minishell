/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeshin <jeshin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 12:56:23 by jeshin            #+#    #+#             */
/*   Updated: 2024/04/24 14:37:14 by jeshin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

void check_leak()
{
	system("leaks a.out");
}

int main(int ac, char **av, char **envp){
	t_sig sig;
	char *buf;
	t_dq *env;
	t_tree	*tree;
	t_list	*tk;
	if (set_signal(&(sig.sa_int),&(sig.sa_quit))) //시그널 처리
		return (EXIT_FAILURE);
	// bash-3.2$에서 -이후 숫자가 bash버전임. 버전가져와야함.안가져와도 되나? ㅋㅋ
	// int version = get_bash_version(envp);
	make_my_env(envp, env);
	while(TRUE)
	{
		buf = readline("bash-3.2$ ");
		if (buf == 0) //ctrl+d로 eof가 들어오면 
			put_exit_when_eof();
		if (ft_strlen(buf)) //노드 헤드가 있다면 history에 추가 
			add_history(buf);// 방향키로 이전에 입력한 커맨드 불러올 수 있음.
		tk = tokenize(buf); //사용할 때 이렇게 사용하면 되는지?
		tree = make_tree(tree, tk, env->head);
		if (open_n_link_fds(tree)); //erro처리 필요

		go_exec(tree,env);
		free(buf);
	}
	return (EXIT_SUCCESS);
}