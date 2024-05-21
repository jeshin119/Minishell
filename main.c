/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeshin <jeshin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 15:58:51 by jeshin            #+#    #+#             */
/*   Updated: 2024/05/20 18:44:51 by jeshin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

static void	init_tree_tk_lst(t_tree **tree, t_list **tk_list)
{
	*tree = 0;
	*tk_list = 0;
}

static void	free_member(t_tree *tree, t_list *tk_list, char *buf)
{
	free(buf);
	free_all(tree, tk_list);
}

static void	limit_argc(int argc, char **argv)
{
	if (argc > 1)
	{
		printf("%s don't need to any arguments\n", argv[0]);
		exit(EXIT_FAILURE);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_tree	*tree;
	t_list	*tk_list;
	t_dq	env;
	char	*buf;

	limit_argc(argc, argv);
	make_my_env(envp, &env);
	while (TRUE)
	{
		init_tree_tk_lst(&tree, &tk_list);
		set_signal_in_main();
		buf = readline("tash-3.2$ ");
		update_prev_status(&env);
		if (check_buf(&buf) == EXIT_FAILURE)
		{
			system("leaks --list minishell");
			continue ;
		}
		tk_list = tokenize(buf, 0);
		tree = make_tree(tree, tk_list);
		exec_tree(&buf, tree, &env);
		free_member(tree, tk_list, buf);
		system("leaks --list minishell");
	}
	clear_dq(&env);
	system("leaks --list minishell");
	return (EXIT_SUCCESS);
}
