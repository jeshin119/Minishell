/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   err.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeshin <jeshin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 17:44:07 by jeshin            #+#    #+#             */
/*   Updated: 2024/05/08 17:45:47 by jeshin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	put_errmsg_syntax_err(t_tree *tree)
{
	printf("bash: syntax error near unexpected token ");
	if (tree->tk_list -> ctrl_token == PIPE)
		printf("'|'\n");
	else if (tree->tk_list -> prev && tree->tk_list -> prev -> ctrl_token)
		printf("'%s'\n", tree->tk_list -> token);
	else if (tree->tk_list -> next)
		printf("'%s'\n", tree->tk_list -> next -> token);
	else
		printf("'newline'\n");
}