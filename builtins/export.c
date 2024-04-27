/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeshin <jeshin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 15:45:34 by jeshin            #+#    #+#             */
/*   Updated: 2024/04/15 16:27:47by jeshin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	mke_my_env(char **e, t_dq *env)
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

static void put_elem(t_node *this)
{
	ft_putstr(this->name);
	write(1,"=\"",2);
	ft_putstr(this->val);
	write(1,"\"\n",2);
}

static int put_elem_in_ascii_order(t_dq *env)
{
	t_node	*here;
	t_node	*cmp;
	t_node	*put;
	int		*visited;
	int		i;
	int		is_prted;
	int		j;

	visited = (int *)malloc(sizeof(int)*env->size);
	i = -1;
	while (++i < env->size)
		visited[i] = 0;

	here = env->head;
	i = 0;

	while (here)
	{
		put = env->head;
		cmp = env->head;
		is_prted = 0;
		j = 0;
		while (cmp)
		{
			if (here == cmp)
			{
				cmp = cmp->next;
				j++;
				continue;
			}
			if (visited[j])
			{
				cmp = cmp->next;
				j++;
				continue;
			}
			if (ft_strncmp(put->name, cmp->name, ft_strlen(put->name)) > 0)
			{
				put = cmp;
				is_prted = j;
			}
			cmp = cmp->next;
			j++;
		}
		visited[is_prted] = 1;
		put_elem(put);
		here = here->next;
		i++;
	}
	free(visited);
	return (EXIT_SUCCESS);
}

void	_export(char *name, char *val, t_dq *env)
{
	int	*order;

	if (name == 0 || *name == 0)
		put_elem_in_ascii_order(env);
	push_back_dq(env, name, val);
	exit (EXIT_SUCCESS);
}

//test//
// int main(int ac,char **av,char **envp){
// 	t_dq env;
// 	char *set[5] = {"ctt","bta","atc","atb",NULL};
// 	mke_my_env(envp, &env);
// 	_export("a","hihi",&env);
// 	print_all_dq(&env);
// }