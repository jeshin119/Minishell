/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seunghan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 18:03:38 by seunghan          #+#    #+#             */
/*   Updated: 2023/11/02 18:56:16 by seunghan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

static int	ft_countword(const char *s, char c)
{
	size_t	word;
	size_t	i;

	word = 0;
	i = 0;
	while (s[i])
	{
		if (s[i] == c && s[i + 1] != c && s[i + 1] != '\0')
			word++;
		i++;
	}
	if (s[0] != c && s[0] != '\0')
		word++;
	return (word);
}

static void	arr_free(char **str_arr)
{
	size_t	i;

	i = 0;
	while (str_arr[i])
		free(str_arr[i++]);
	free(str_arr);
	return ;
}

static char	**split_words(const char *s, char c, char **str_arr, size_t word)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (s[i])
	{
		if (s[i] == c && s[i + 1] != c && s[i + 1] != '\0')
		{
			j = 0;
			while (s[i + 1] != c && s[i + 1] != '\0')
			{
				i++;
				j++;
			}
			str_arr[word] = ft_substr(s, i + 1 - j, j);
			if (!(str_arr[word]))
			{
				arr_free(str_arr);
				return (0);
			}
			word++;
		}
		i++;
	}
	return (str_arr);
}

static char	**split_first_word(const char *s, char c, char **str_arr)
{
	size_t	i;

	i = 0;
	if (s[0] != c && s[0] != '\0')
	{
		while (s[i] != c && s[i] != '\0')
			i++;
		str_arr[0] = ft_substr(s, 0, i);
		if (!(str_arr[0]))
		{
			arr_free(str_arr);
			return (0);
		}
	}
	return (str_arr);
}

char	**ft_split(const char *s, char c)
{
	char	**str_arr;
	size_t	max_word;
	size_t	word;

	word = 0;
	if (s[0] != c)
		word++;
	max_word = ft_countword(s, c);
	str_arr = (char **)malloc(sizeof(char *) * (max_word + 1));
	if (!(str_arr))
		return (0);
	str_arr[max_word] = 0;
	str_arr = split_first_word(s, c, str_arr);
	if (!(str_arr))
		return (0);
	str_arr = split_words(s, c, str_arr, word);
	if (!(str_arr))
		return (0);
	return (str_arr);
}
