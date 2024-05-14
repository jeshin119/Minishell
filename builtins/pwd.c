/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeshin <jeshin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 17:24:19 by jeshin            #+#    #+#             */
/*   Updated: 2024/05/14 19:02:33 by jeshin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	_pwd(void)
{
	char	*bkup;
	char	*buf;
	int		size;

	bkup = 0;
	size = 1024;
	while (TRUE)
	{
		buf = malloc(sizeof(char) * size);
		bkup = ft_strdup(getcwd(buf, size));
		free(buf);
		if (bkup != 0)
			break ;
		if (size > 1024 && bkup == 0)
		{
			perror(NULL);
			return (EXIT_FAILURE);
		}
		size *= 2;
	}	
	ft_putstr(bkup);
	write(1, "\n", 1);
	free(bkup);
	return (EXIT_SUCCESS);
}
