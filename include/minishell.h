/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeshin <jeshin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 17:45:24 by seunghan          #+#    #+#             */
/*   Updated: 2024/04/24 11:59:41 by jeshin           ###   ########.fr       */
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
# define END_LINE 7
# define ENV 8
# define D_QUOTE 9
# define S_QUOTE 10
# define QUOTES 9
# define NO_DR 0
# define ON 1
# define OFF 0
# define NONE -1
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
# include "../libft/libft.h"
# include "my_deque.h"
# include "pipex_bonus.h"

typedef struct s_tree
{
	t_list			*tk_list;
	int				idx;
	int				chked;
	int				ctrl_token;
	int				end_flag;
	int				*tk_idx_set;
	struct s_tree	*next_left;
	struct s_tree	*next_right;
	struct s_tree	*prev;
}	t_tree;

//signal 처리 구조체 
typedef struct s_sig
{
	struct sigaction sa_int;
	struct sigaction sa_quit;
}	t_sig;

//parse
void	meta_split(char *s, t_list **tk_list, int *i);
void	env_replace(char *s, t_list **tk_list, t_node *env_list, int *i);
void	syntax_error_exit(t_list *tk_list);
void	preorder_travel(t_tree *now, t_list *tk_list);
int		pipe_chk(t_list *tk_list);
int		meta_chk(char *s, int i, int meta_value);
int		right_rd_chk(t_list *tk_list);
int		get_double_direct(int direct);
t_tree	*make_tree(t_tree *now, t_list *tk_list, t_node *env_list);
t_tree	*malloc_tree_node(t_tree *now, t_list *tk_list, int direct);
t_tree	*malloc_cmd_node(t_tree *now, t_list *tk_list, int cmd_cnt);
t_tree	*make_cmd_node(t_tree *now, t_list *tk_list);
t_tree	*go_to_subroot(t_tree *now);
t_tree	*go_to_pipe(t_tree *now);
t_tree	*make_pipe_node(t_tree *now, t_list *tk_list);
t_tree	*make_rd_node(t_tree *now, t_list *tk_list, int direct);
t_tree	*reassembly(t_tree *now, t_list *tk_list);
t_list	*tokenize(char *cmd_line);
t_list	*token_split(t_list *tk_list, char *s);
t_tree	*parse(char *line, t_dq *env);

//builtins
int		_echo(char *opt, char *str);
int		_cd(char *path, t_dq *env);
int		_pwd(void);
int		_export(char *name, char *val, t_dq *env);
void	_unset(t_dq *env, char *remove);
void	_env(t_dq *env);
void	__exit(void);

//pipe.c
int get_pipe_num_from_tree(t_tree *tre);
int	**open_pipes(int num);

//open_fd.c
int	open_heredoc_n_return(t_tree *tree);
int	open_infile_n_return(t_tree *tree);
int	open_outfile_n_return(t_tree *tree);
int	open_appending_n_return(t_tree *tree);

//handle_signal.c
void	handle_int();
int		set_signal(struct sigaction *sa_int, struct sigaction *sa_quit);
void	put_exit_when_eof(void);

//utils.c
char 	*get_nth_token_from_lst(t_tree *tree, int nth);
void	make_my_env(char **e, t_dq *env);
void	my_dup2(int rd, int wr);
#endif
