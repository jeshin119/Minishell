/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seunghan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 20:06:38 by seunghan          #+#    #+#             */
/*   Updated: 2024/05/06 13:24:28 by seunghan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# include <stdlib.h>
# include <unistd.h>

int		ft_strlen(const char *s);
char	*ft_strdup(const char *s1);
int		ft_strncmp(const char *s1, const char *s2, size_t c);
char	*ft_substr(char const *s, int start, int len);
char	*ft_strjoin(char *s1, char *s2);
char	*ft_strtrim(char const *s1, char const *set);
void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);
void	ft_putendl_fd(char *s, int fd);
void	ft_putnbr_fd(int n, int fd);
char	**ft_split(const char *s, char c);

typedef struct s_env
{
	int	len;
	int	d_quote;
}	t_env;

typedef struct s_list
{
	char			*token;
	int				token_idx;
	int				ctrl_token;
	int				quote_to_space;
	struct s_list	*next;
	struct s_list	*prev;
	t_env			*env_lset;
}	t_list;

t_list	*ft_lstnew(t_list *now);
int		ft_lstsize(t_list *lst);
t_list	*ft_lstlast(t_list *lst);

#endif
