/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeshin <jeshin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 19:46:17 by jeshin            #+#    #+#             */
/*   Updated: 2024/04/22 17:20:27 by jeshin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex_bonus.h"

static char	**get_envtab(char *envp[])
{
	int		i;
	char	**tab;
	char	*tmp;

	i = -1;
	tmp = 0;
	while (envp[++i])
	{
		if (ft_strnstr(envp[i], "PATH", 4))
		{
			tmp = ft_strnstr(envp[i], "PATH", 4) + 5;
			tab = ft_split(tmp, ':');
			i = -1;
			while (tab[++i])
			{
				tmp = ft_strjoin(tab[i], "/");
				free(tab[i]);
				tab[i] = tmp;
			}
			return (tab);
		}
	}
	return (0);
}

static int	link_lst(t_lst **lst, char *s, t_str_ags *ags)
{
	t_lst	*new;

	if (get_mid_substr(s, &(ags->tmp_s), ags->i, ags->pos) == -1)
		return (-1);
	if (ags->have_lst_made == FALSE)
	{
		*lst = lstnew(((char *)ags->tmp_s));
		if (lst == 0)
			return (-1);
		ags->have_lst_made = TRUE;
	}
	else
	{
		new = lstnew((char *)ags->tmp_s);
		if (new == 0)
			return (-1);
		lstadd_back(lst, new);
	}
	if (s[ags->i] != 0)
	{
		while (s[ags->i] == ' ')
			(ags->i)++;
		ags->pos = ags->i;
	}
	return (0);
}

static int	get_cmdlst(char *s, t_lst **cmd_lst)
{
	t_str_ags	ags;

	init_str_agr(&ags);
	while (s[ags.i])
	{
		if (s[ags.i] == '\'' && ags.dq == FALSE)
			ags.sq = !ags.sq;
		else if (s[ags.i] == '"' && ags.sq == FALSE)
			ags.dq = !ags.dq;
		if (ags.sq == FALSE && ags.dq == FALSE \
		&& (s[ags.i] == ' ' || s[ags.i] == 0))
			link_lst(cmd_lst, s, &ags);
		else
			(ags.i)++;
	}
	if (ags.sq || ags.dq)
	{
		lstclear(cmd_lst, free);
		return (-1);
	}	
	if (s[ags.i] == 0)
		link_lst(cmd_lst, s, &ags);
	return (0);
}

int	get_opts(char *s, char ***tab)
{
	t_lst	*lst;
	t_lst	*head;
	int		size_lst;
	int		i;

	if (get_cmdlst(s, &lst) == -1)
		exit_with_errmsg("cmd error\n");
	head = lst;
	size_lst = lstsize(lst);
	*tab = (char **)malloc(sizeof(char *) * (size_lst + 1));
	if (*tab == 0)
	{
		lstclear(&lst, free);
		return (-1);
	}
	(*tab)[size_lst] = 0;
	i = -1;
	while (++i < size_lst)
	{
		(*tab)[i] = ft_strdup((lst->content));
		lst = lst->next;
	}
	lst = head;
	lstclear(&lst, free);
	return (0);
}

char	*get_path(char *cmd, char *envp[])
{
	char	**envtab;
	char	*path;
	int		i;

	if (cmd == 0)
		return (0);
	envtab = get_envtab(envp);
	if (envtab == 0)
		exit_with_errmsg("envtab error");
	i = -1;
	while (envtab[++i])
	{
		path = ft_strjoin(envtab[i], cmd);
		if (access(path, F_OK | X_OK) == 0)
		{
			free_tab(&envtab);
			return (path);
		}
		free(path);
	}
	free_tab(&envtab);
	perror("127error");
	exit(127);
	return (0);
}
