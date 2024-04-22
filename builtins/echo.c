/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeshin <jeshin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 13:13:55 by jeshin            #+#    #+#             */
/*   Updated: 2024/04/22 15:23:00 by jeshin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	_echo(char *opt, char *str)
{
	int	line_filp;

	line_filp = 1;
	if (opt != 0 && ft_strncmp(opt, "-n", 3) == 0)
		line_filp = 0;
	if (line_filp)
	{
		write(1, str, ft_strlen(str));
		write(1, "\n", 1);
		return (0);
	}
	write(1, str, ft_strlen(str));
	return (0);
}
