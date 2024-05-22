/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeshin <jeshin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 17:24:19 by jeshin            #+#    #+#             */
/*   Updated: 2024/05/22 16:52:57 by jeshin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	_pwd(void)
{
	char	*buf;
	int		size;

	size = 4096;
	buf = malloc(sizeof(char) * (size + 1));
	getcwd(buf, size);
	if (buf == NULL)
	{
		ft_putstr_fd("bash: pwd: ", 2);
		perror(NULL);
		free(buf);
		return (EXIT_FAILURE);
	}
	printf("%s\n", buf);
	free(buf);
	return (EXIT_SUCCESS);
}
