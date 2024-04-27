/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeshin <jeshin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 13:07:49 by jeshin            #+#    #+#             */
/*   Updated: 2024/05/01 13:00:58 by jeshin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/minishell.h"

char	*get_path(char *cmd, t_dq *env)
{
	if (cmd == 0)
		return NULL;
	t_node *start=env->head;
	char *path;
	while(start){
		if (ft_strncmp(start->name,"PATH",4)==0)
			break;
		start=start->next;
	}
	
	char **tab = ft_split(start->val, ':');
	int i=-1;
	while(tab[++i]){
		char *tmp = ft_strjoin_no_free(tab[i],"/");
		free(tab[i]);
		tab[i] = tmp;
	}
	i=-1;
	while(tab[++i]){
		path = ft_strjoin_no_free(tab[i],cmd);
		if (access(path, F_OK | X_OK) == 0)
		{
			free_tab(tab);
			return (path);
		}
		free(path);
	}
	free_tab(tab);
	ft_putstr_fd("bash: ",2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": ",2);
	perror(NULL);
	exit(127);
	return (NULL);
}
