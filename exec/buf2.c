/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buf2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeshin <jeshin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 17:23:34 by jeshin            #+#    #+#             */
/*   Updated: 2024/05/13 19:17:37 by jeshin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	check_behind(int i, char *s)
{
	int		k;
	int		depth;
	int 	deli;
	char	*set;

	depth = 0;
	set = "<|>";
	k = -1;
	while (set[++k])
	{
		if (set[k] == s[i])
			deli = k;
	}
	printf("deli : %c\n",set[deli]);
	k = i;
	while (s[++k] && (size_t)k < ft_strlen(s))
	{
		if (ft_isspace(s[k]))
			continue ;
		if (ft_isalnum(s[k]))
			return (EXIT_SUCCESS);
		if (depth == 0 && \
		(s[k] == set[(deli + 1) % 3] || s[k] == set[(deli + 2) % 3]))
			return (k);
		depth++;
	}
	return (EXIT_SUCCESS);
}

static int check(char *s, int i, int *status)
{
	int ret;
	ret = 0;
	if (s[i] == '<' || s[i] == '>' || s[i] == '|')
	{
		ret = check_behind(i, s);
		if (ret)
		{
			*status = ret;
			return (EXIT_FAILURE);
		}
	}
	return (EXIT_SUCCESS);
}

int	check_syntax_err(char *s)
{
	int	i;
	int	sq;
	int	dq;
	int	status;

	if (s == 0)
		return (EXIT_SUCCESS);
	i = -1;
	while (s[++i])
	{
		if (s[i] == '\'' && dq == FALSE)
			sq = !sq;
		if (s[i] == '"' && sq == FALSE)
			dq = !dq;
		if (sq == FALSE && dq == FALSE)
		{
			if (check(s, i, &status))
				return (status);
		}
	}
	return (EXIT_SUCCESS);
}

// int main(){
// 	char *s = "echo <> |";
// 	printf("%d",check_syntax_err(s));
// }