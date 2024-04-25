/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeshin <jeshin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 12:56:23 by jeshin            #+#    #+#             */
/*   Updated: 2024/04/25 17:50:59 by jeshin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

void check_leak()
{
	system("leaks a.out");
}
void prt_sbtl(t_tree_info *trif)
{
	t_subtree *here = trif->sbt_lst->head;
	printf("\n*********************************\n");
	while(here){
		printf("cmd : %s,\t",here->cmd);
		if (here->opt){
			printf("opt : ");
			for(int i=0;here->opt[i]!=0;i++){
				printf("%s ",here->opt[i]);
			}
			printf(",\t");
		}
		printf("infile : %d,\t",here->infile_fd);
		printf("outfile : %d.\n",here->outfile_fd);
		here= here->next;
	}
	printf("\n*********************************\n");
}

int main(int ac, char **av, char **envp){
	t_sig sig;
	char *buf;
	t_dq env;
	t_tree	*tree;
	t_list	*tk_lst;
	t_tree_info tree_info;

	if (set_signal(&(sig.sa_int),&(sig.sa_quit))) //시그널 처리
		return (EXIT_FAILURE);
	// bash-3.2$에서 -이후 숫자가 bash버전임. 버전가져와야함.안가져와도 되나?
	// int version = get_bash_version(envp);
	make_my_env(envp, &env);
	while(TRUE)
	{
		buf = readline("bash-3.2$ ");
		if (buf == 0) //ctrl+d로 eof가 들어오면 
			put_exit_when_eof();
		if (ft_strlen(buf)) //노드 헤드가 있다면 history에 추가 
			add_history(buf);// 방향키로 이전에 입력한 커맨드 불러올 수 있음.
		char *line = ft_strdup(buf);
		tk_lst = tokenize(line);
		tree = make_tree(tree, tk_lst, env.head);

		if (init_tree_info(tree , &tree_info))
			return (EXIT_FAILURE); // 트리정보 기록에 실패할 경우
		make_subtree_lst(tree, tree_info.sbt_lst); //erro처리 필요
		// printf("line : %s\n",line);
		prt_sbtl(&tree_info);
		// free(buf);
	}
	return (EXIT_SUCCESS);
}