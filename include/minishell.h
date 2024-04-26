/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeshin <jeshin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 17:45:24 by seunghan          #+#    #+#             */
/*   Updated: 2024/04/26 18:08:25 by jeshin           ###   ########.fr       */
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
# include <errno.h>
# include "../libft/libft.h"
# include "my_deque.h"

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

//서브트리 구조체 
typedef struct s_subtree
{
	int					infile_fd;
	int					outfile_fd;
	int					is_heredoc;
	int					is_appending;
	char				*infile;
	char				*outfile;
	char				*cmd;
	char				**opt;
	struct s_subtree	*next;
	struct s_subtree	*prev;
} t_subtree;

//서브트리 리스트구조체
typedef struct s_sbt_lst
{
	t_subtree *head;
	t_subtree *tail;
}	t_sbt_lst;

//트리정보 구조체 
typedef struct s_tree_info
{
	struct s_sbt_lst *sbt_lst;
	int **pipe_tab;
	int pipe_num;
}	t_tree_info;

//시그널처리
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
int 	get_pipe_num_from_tree(t_tree *tre);
int 	open_pipes(int num, int ***pipe_fd_tab);

//tree_info.c
int	 init_tree_info(t_tree *tree, t_tree_info *tr_info);
void	reset_tree_info(t_tree_info *info);
//subtree.c
void	make_subtree_lst(t_tree *tree, t_sbt_lst *sbtl);

//subtree_utils.c
void	prt_sbtl(t_tree_info *trif);
void	free_subtree(t_subtree *sbtr);

//open_file.c
int		get_fd(t_tree *tree);

//handle_signal.c
void	handle_int();
int		set_signal(struct sigaction *sa_int, struct sigaction *sa_quit);
void	put_exit_when_eof(void);

//utils.c
char 	*get_nth_token_from_lst(t_tree *tree, int nth);
char 	**get_opt_from_lst(t_tree *tree);
void	make_my_env(char **e, t_dq *env);
void	my_dup2(int rd, int wr);
void	free_tab(char	**tab);
#endif
