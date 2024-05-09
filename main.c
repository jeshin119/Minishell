/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeshin <jeshin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 15:58:51 by jeshin            #+#    #+#             */
/*   Updated: 2024/05/09 18:19:12 by jeshin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

void	check_leak(void)
{
	system("leaks minishell");
}

int	main(int ac, char **av, char **envp)
{
	t_sig	sig;
	t_dq	env;
	t_tree	*tree;
	t_list	*tk_lst;
	char	*line;
	char	*buf;

	make_my_env(envp, &env);
	while (TRUE)
	{
		tree = 0;
		tk_lst = 0;
		set_signal(&(sig.sa_int), &(sig.sa_quit));
		buf = readline("tash-3.2$ ");
		if (check_buf(&buf, &env) == EXIT_FAILURE)
			continue ;
		tk_lst = tokenize(line);
		tree = make_tree(tree, tk_lst);
		if (exec_tree(tree, &env))
		{
			free_all(tree, tk_lst);
			continue ;
		}
		free(line);
		free_all(tree, tk_lst);
		// system("leaks minishell");
	}
	atexit(check_leak);
	return (EXIT_SUCCESS);
}
