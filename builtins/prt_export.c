/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prt_export.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeshin <jeshin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 15:09:24 by jeshin            #+#    #+#             */
/*   Updated: 2024/06/03 18:19:07 by jeshin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	prt_export(t_dq *env)
{
	t_node	*node;

	node = env->head;
	while (node)
	{
		if (!ft_strncmp(node->name, "?", 2))
		{
			node = node->next;
			continue ;
		}
		if (!ft_strncmp(node->name, "~", 2))
		{
			node = node->next;
			continue ;
		}
		printf("declare -x %s", node->name);
		if (node->val)
			printf("=\"%s\"\n", node->val);
		else
			printf("\n");
		node = node->next;
	}
	return (EXIT_SUCCESS);
}
