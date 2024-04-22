/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_tmp.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeshin <jeshin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 18:36:38 by jeshin            #+#    #+#             */
/*   Updated: 2024/04/22 19:23:04 by jeshin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

int	exec_builtins(char *cmd,char *opt,t_dq *env)
{
	if (cmd == 0)
		return (EXIT_FAILURE);
	if (!ft_strncmp(cmd, "echo", 5))
		_echo(opt,cmd);
	else if(!ft_strncmp(cmd, "cd", 3))
		_cd(cmd,env);
	else if(!ft_strncmp(cmd, "pwd", 4))
		_pwd();
	else if(!ft_strncmp(cmd, "export", 7))
		_export(opt[0],opt[1],env);
	else if(!ft_strncmp(cmd, "unset", 6))
		_unset(env,opt);
	else if(!ft_strncmp(cmd, "env", 4))
		_env(env);
	else if(!ft_strncmp(cmd, "exit", 5))
		_exit_();
	else
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
int exec_not_builtin()
{
	t_ags	ags;
	int		status;
	int		i;

	init_ags(&ags, ac, av);
	while (++(ags.idx) < ags.n_cmd)
		go_child(ags, env);
	close_all_pipe(&ags);
	i = -1;
	while (++i < ags.n_cmd)
		waitpid(-1, &status, 0);
	close(ags.in_f_fd);
	close(ags.out_f_fd);
	free_all(&ags);

}

int	ggo_exec(t_tree *tre, t_list *tk, t_dq *env)
{
	if (tre->end_flag || tre == 0)
		return (EXIT_SUCCESS);
	if (exec_bulitin())
		if (exec_not_builtin())
			return (EXIT_FAILURE);
	ggo_exec(tre->next_left,tk,env);
	ggo_exec(tre->next_right,tk,env);
}


int	go_exec(t_tree *tre, t_list *tk, t_dq *env)
{
	care_pipes(tre);


	if (tre->end_flag)
		return (EXIT_SUCCESS);
	ggo_exec(tre->next_left,tk,env);
	while()
	return (EXIT_SUCCESS);
}
