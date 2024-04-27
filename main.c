/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeshin <jeshin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 12:56:23 by jeshin            #+#    #+#             */
/*   Updated: 2024/05/01 11:27:17jeshin           ###   ########.fr       */
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
	char *line;
	char *buf;

	if (set_signal(&(sig.sa_int),&(sig.sa_quit)))
		return (EXIT_FAILURE);
	make_my_env(envp, &env);
	while (TRUE)
	{
		buf = readline("mmmmbash-3.2$ ");
		line = check_buf(buf);
		if (line == NULL)
			continue;
		//////////////////////////////////
		tk_lst = tokenize(line);
		tree = make_tree(tree, tk_lst, env.head);
		//////////////////////////////////
		if (init_tree_info(tree , &tree_info))
			return (EXIT_FAILURE);
		make_subtree_lst(tree, tree_info.sbt_lst); //erro처리 필요
		exec_subtree(tree , &tree_info, &env);
		close_all_pipe(tree_info.pipe_num, tree_info.pipe_tab);
		int state;
		for(int i=0;i<tree_info.pipe_num+1;i++){
			waitpid(-1,&state,0);
		}
		// close(tree_info.sbt_lst->tail->infile_fd);
		// close(tree_info.sbt_lst->tail->outfile_fd);
		reset_tree_info(&tree_info);
		free(line);
		tree = 0; tk_lst = 0;
	}
	return (EXIT_SUCCESS);
}