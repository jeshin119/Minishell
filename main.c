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

int main(int ac, char **av, char **envp)
{
	t_sig sig;
	t_dq env;
	t_tree	*tree;
	t_list	*tk_lst;
	char *line;
	char *buf;

	make_my_env(envp, &env);
	while (TRUE)
	{
		set_signal(&(sig.sa_int), &(sig.sa_quit));
		buf = readline("tash-3.2$ ");
		line = check_buf(buf);
		if (line == NULL)
			continue;
		tk_lst = tokenize(line);
		tree = make_tree(tree, tk_lst);
		if (exec_tree(tree, &env))
			continue ;
		free(line);
		tree = 0;
		tk_lst = 0;
	}
	return (EXIT_SUCCESS);
}
