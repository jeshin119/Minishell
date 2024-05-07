/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seunghan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 13:17:50 by seunghan          #+#    #+#             */
/*   Updated: 2024/05/06 13:27:23 by seunghan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*void	cl()
{
	system("leaks a.out");
}*/

void	mke_my_env(char **e, t_dq *env)
{
	char	**tmp;

	init_dq(env);
	while (*e)
	{
		tmp = ft_split(*e, '=');
		push_back_dq(env, tmp[0], tmp[1]);
		free(tmp);
		e++;
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_tree	*now;
	t_list	*tk_list;
	char	*cmd_line_no_m;
	char	*cmd_line;
	int		i;
	t_dq	env;
	t_node	*env_list;

	argc = 0;
	argv = 0;
	mke_my_env(envp,&env);
	//unset(&env,"a");
	env_list = env.head;
	/*while(env_list)
	{
		printf("%s = ",env_list -> name);
		printf("%s\n",env_list -> val);
		env_list = env_list -> next;
	}
	env_list = env.head;*/
	i = 0;
	now = 0;
	cmd_line_no_m = readline("my_bash : ");
	while (cmd_line_no_m[i])
		i++;
	cmd_line = (char *)malloc(i + 1);
	i = 0;
	while (cmd_line_no_m[i])
	{
		cmd_line[i] = cmd_line_no_m[i];
		i++;
	}
	cmd_line[i] = 0;
	tk_list = tokenize(cmd_line);
	/*while (tk_list)
	{
		i = 0;
		printf("%s---%d\n", tk_list -> token, tk_list -> token_idx);
		while (tk_list -> env_lset && (tk_list -> env_lset)[i] != END)
		{
			printf("%d-->env  ", (tk_list -> env_lset)[i]);
			i++;
		}
		tk_list = tk_list -> next;
	}*/
	now = make_tree(now, tk_list);
	preorder_travel(now, tk_list, env_list);
	free_all(now, tk_list);
	free(cmd_line);
	free(cmd_line_no_m);
	//atexit(cl);
	return (0);
}
