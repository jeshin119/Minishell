/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeshin <jeshin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 13:17:50 by seunghan          #+#    #+#             */
/*   Updated: 2024/04/25 17:52:40 by jeshin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_tree	*parse_before(char *line, t_dq *env)
{
	t_tree	*now;
	t_list	*tk_list;
	char	*cmd_line_no_m;
	char	*cmd_line;
	int		i;
	t_node	*env_list;

	//unset(&env,"a");
	env_list = env->head;

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
		printf("%s---%d\n", tk_list -> token, tk_list -> ctrl_token);
		tk_list = tk_list -> next;
	}*/
	return (now = make_tree(now, tk_list, env_list));
	preorder_travel(now, tk_list);
	return (0);
}
