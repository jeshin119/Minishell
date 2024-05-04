/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeshin <jeshin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 18:36:38 by jeshin            #+#    #+#             */
/*   Updated: 2024/05/07 12:51:44 by jeshin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int status;

static void	handle_int_to_put_mark(int signum)
{
	write(1, "^C\n", 3);
}

void	exec_tree(t_tree *tree, t_dq *env)
{
	t_tree_info	tree_info;
	int			i;

	init_tree_info(tree, &tree_info);
	make_subtree_lst(tree, tree_info.sbt_lst);
	signal(SIGINT, handle_int_to_put_mark);
	exec_subtree(tree, &tree_info, env);
	close_all_pipe(tree_info.pipe_num, tree_info.pipe_tab);
	i = -1;
	while (++i < tree_info.pipe_num + 1){
		waitpid(-1, &status, 0);
		// if (WIFEXITED(status)){
		// 	printf("ee child status : %d\n", WEXITSTATUS(status));
		// }
		// else if (WIFSIGNALED(status)){
		// 	printf("ss child status : %d\n", WTERMSIG(status)+128);
		// }
	}
	reset_tree_info(&tree_info);
}
