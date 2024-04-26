/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeshin <jeshin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 12:56:23 by jeshin            #+#    #+#             */
/*   Updated: 2024/04/26 17:33:46 by jeshin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

void	check_leak(void)
{
	system("leaks a.out");
}

int main(int ac, char **av, char **envp){
	t_sig sig;
	t_dq env;
	t_tree	*tree;
	t_list	*tk_lst;
	t_tree_info	tree_info;
	char *buf;
	char *line;

	if (set_signal(&(sig.sa_int),&(sig.sa_quit))) //시그널 처리
		return (EXIT_FAILURE);
	make_my_env(envp, &env);
	while(TRUE)
	{
		buf = readline("bash-3.2$ ");
		if (buf == 0)
			put_exit_when_eof();
		if (ft_strlen(buf))
			add_history(buf);
		else{
			free(buf);
			continue;
		}
		line = ft_strdup(buf);
		tk_lst = tokenize(line);
		tree = make_tree(tree, tk_lst, env.head);
		if (init_tree_info(tree , &tree_info))
			return (EXIT_FAILURE);
		make_subtree_lst(tree, tree_info.sbt_lst); //erro처리 필요
		prt_sbtl(&tree_info);
		reset_tree_info(&tree_info);
		free(buf);
		free(line);
	}
	return (EXIT_SUCCESS);
}