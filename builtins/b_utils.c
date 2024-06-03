/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_utils.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeshin <jeshin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 16:31:58 by jeshin            #+#    #+#             */
/*   Updated: 2024/06/03 17:36:08 by jeshin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_node	*get_node_from_env(char *cmp, t_dq *env)
{
	t_node	*here;

	here = env->head;
	while (here)
	{
		if (ft_strncmp(here->name, cmp, ft_strlen(cmp) + 1) == EXIT_SUCCESS)
			return (here);
		here = here->next;
	}
	return (NULL);
}

int	_free(void *m)
{
	if (m != NULL)
	{
		free(m);
		return (EXIT_SUCCESS);
	}
	return (EXIT_FAILURE);
}
