/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeshin <jeshin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 15:58:51 by jeshin            #+#    #+#             */
/*   Updated: 2024/05/13 11:10:58 by jeshin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

void	check_leak(void)
{
	system("leaks --list minishell");
}

void	init_tree_tk_lst(t_tree **tree, t_list **tk_list)
{
	*tree = 0;
	*tk_list = 0;
}

void	free_member(t_tree *tree, t_list *tk_list, char *buf)
{
	free(buf);
	free_all(tree, tk_list);
}

void	limit_argc(int argc, char **argv)
{
	if (argc > 1)
	{
		printf("%s don't need to any arguments\n", argv[0]);
		exit(EXIT_FAILURE);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_sig	sig;
	t_dq	env;
	t_tree	*tree;
	t_list	*tk_list;
	char	*buf;

	limit_argc(argc, argv);
	make_my_env(envp, &env);
	while (TRUE)
	{
		init_tree_tk_lst(&tree, &tk_list);
		set_signal(&(sig.sa_int), &(sig.sa_quit));
		buf = readline("tash-3.2$ ");
		if (check_buf(&buf, &env) == EXIT_FAILURE)
			continue ;
		tk_list = tokenize(buf);
		tree = make_tree(tree, tk_list);
		//exec_tree(tree, &env);
		free_member(tree, tk_list, buf);
		check_leak();
	}
	clear_dq(&env);
	return (EXIT_SUCCESS);
}
