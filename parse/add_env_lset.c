/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_env_lset.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seunghan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 12:00:57 by seunghan          #+#    #+#             */
/*   Updated: 2024/05/29 12:10:49 by seunghan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static t_env	*malloc_env_lset_new(t_list *tk_list, t_env *env_lset_arg)
{
	int		e_idx;
	int		e_idx_new;
	t_env	*env_lset_new;

	e_idx = 0;
	e_idx_new = 0;
	if (!env_lset_arg)
		return (0);
	while (tk_list -> env_lset[e_idx]. len > 0)
		e_idx++;
	while (env_lset_arg[e_idx_new]. len > 0)
		e_idx_new++;
	env_lset_new = (t_env *)malloc(sizeof(t_env) * (e_idx + e_idx_new));
	if (!env_lset_new)
		exit(1);
	return (env_lset_new);
}

void	add_env_lset(t_list *tkl, t_env *env_lset_arg)
{
	int		e_idx;
	t_env	*env_lset_new;

	e_idx = 0;
	env_lset_new = malloc_env_lset_new(tkl, env_lset_arg);
	if (!env_lset_new)
		return ;
	while (tkl -> env_lset[e_idx]. len > 0)
	{
		env_lset_new[e_idx]. len = tkl -> env_lset[e_idx]. len;
		env_lset_new[e_idx]. d_quote = tkl -> env_lset[e_idx]. d_quote;
		env_lset_new[e_idx]. white_flag = tkl -> env_lset[e_idx]. white_flag;
		e_idx++;
	}
	while (env_lset_arg[e_idx]. len > 0)
	{
		env_lset_new[e_idx]. len = env_lset_arg[e_idx]. len;
		env_lset_new[e_idx]. d_quote = env_lset_arg[e_idx]. d_quote;
		env_lset_new[e_idx]. white_flag = env_lset_arg[e_idx]. white_flag;
		e_idx++;
	}
	free(tkl -> env_lset);
	tkl -> env_lset = env_lset_new;
}
