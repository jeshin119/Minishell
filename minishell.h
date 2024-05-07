/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seunghan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 17:45:24 by seunghan          #+#    #+#             */
/*   Updated: 2024/05/05 17:52:22 by seunghan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# define BACK_SLASH 1
# define UPP 1
# define LEFT 2
# define RIGHT 3
# define HERE_DOC 4
# define D_RIGHT 5
# define PIPE 6
# define ENV 8
# define D_QUOTE 9
# define S_QUOTE 10
# define QUOTES 9
# define NO_DR 0
# define ON 1
# define OFF 0
# define END -1
# define S_Q_ENV -2
# include <unistd.h>
# include <stdlib.h>
# include <signal.h>
# include <stdio.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <dirent.h>
# include <string.h>
# include <sys/ioctl.h>
# include <termios.h>
# include <termcap.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "libft/libft.h"
# include "my_deque.h"

typedef struct s_tree
{
	t_list			*tk_list;
	int				idx;
	int				chked;
	int				ctrl_token;
	int				ambi_flag;
	int				end_flag;
	int				*tk_idx_set;
	struct s_tree	*next_left;
	struct s_tree	*next_right;
	struct s_tree	*prev;
}	t_tree;

void	meta_split(char *s, t_list **tk_list, int *i);
void	syntax_error_exit(t_list *tk_list);
void	preorder_travel(t_tree *now, t_list *tk_list, t_node *env_list);
void	env_chk(t_tree *now, t_node *env_list);
void	env_len_chk(t_list *tk_list, char *token, int meta_value);
void	rd_empty_chk(t_tree *now, char *exp_token);
void	rd_space_chk(char *env, t_tree *now, int d_quote);
void	free_all(t_tree *tree, t_list *tk_list);
void	free_tk_idx_set(t_tree *tree);
void	free_next_node(t_tree *tree);
void	go_to_first(t_tree **tree, t_list **tk_list);
int		pipe_chk(t_list *tk_list);
int		meta_chk(char *s, int i, int meta_value);
int		right_rd_chk(t_list *tk_list);
int		quote_closed_chk(char *s, int i);
int		get_double_direct(int direct);
int		env_name_len_chk(char *s, int *i);
int		env_first_ch_chk(char *s, int i);
int		name_valid_chk(char *name, char *s, int i);
int		handle_qt(t_env *env_lset_new, int env_len, int e_idx, int m_v);
char	*get_front_str(char *token, char *s, int i, int *front_len);
t_tree	*make_tree(t_tree *now, t_list *tk_list);
t_tree	*malloc_tree_node(t_tree *now, t_list *tk_list, int direct);
t_tree	*malloc_cmd_node(t_tree *now, t_list *tk_list, int cmd_cnt);
t_tree	*make_cmd_node(t_tree *now, t_list *tk_list);
t_tree	*go_to_subroot(t_tree *now);
t_tree	*go_to_pipe(t_tree *now);
t_tree	*make_pipe_node(t_tree *now, t_list *tk_list);
t_tree	*make_rd_node(t_tree *now, t_list *tk_list, int direct);
t_tree	*reassembly(t_tree *now, t_list *tk_list);
t_tree	*free_sub_tree(t_tree *tree);
t_list	*tokenize(char *cmd_line);
t_list	*token_split(t_list *tk_list, char *s);
t_list	*mv_to_valid_token(t_tree *now, int i);
t_node	*chk_valid_env(t_tree *now, char *s, int i, t_node *env_list);
t_node	*env_name_chk(char *s, t_node *env_list, int i);
t_env	*ini_env_lset(t_env *env_lset_new, int env_cnt);

#endif
