/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeshin <jeshin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 17:45:24 by seunghan          #+#    #+#             */
/*   Updated: 2024/05/15 16:20:21 by jeshin           ###   ########.fr       */
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
# include <errno.h>
# include "../libft/libft.h"
# include "my_deque.h"

typedef struct s_tree
{
	t_list			*tk_list;
	int				idx;
	int				chked;
	int				ctrl_token;
	int				ambi_flag;
	int				end_flag;
	int				exit_code;
	int				*tk_idx_set;
	struct s_tree	*next_left;
	struct s_tree	*next_right;
	struct s_tree	*prev;
}	t_tree;

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
}	t_subtree;

//subtree list
typedef struct s_sbt_lst
{
	t_subtree	*head;
	t_subtree	*tail;
}	t_sbt_lst;

typedef struct s_tree_info
{
	struct s_sbt_lst	*sbt_lst;
	int					**pipe_tab;
	int					pipe_num;
}	t_tree_info;

typedef struct s_sig
{
	struct sigaction	sa_int;
	struct sigaction	sa_quit;
}	t_sig;

int		g_status;

//parse
void	meta_split(char *s, t_list **tk_list, int *i);
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
t_tree	*syntax_error_malloc(t_tree *now, t_list *tk_list, int meta_value);
t_tree	*free_sub_tree(t_tree *tree);
t_list	*tokenize(char *cmd_line);
t_list	*token_split(t_list *tk_list, char *s);
t_list	*mv_to_valid_token(t_tree *now, int i);
t_node	*chk_valid_env(t_tree *now, char *s, int i, t_node *env_list);
t_node	*env_name_chk(char *s, t_node *env_list, int i);
t_env	*ini_env_lset(t_env *env_lset_new, int env_cnt);
t_tree	*parse(char *line, t_dq *env);

//exec
//tree_info.c
void	init_tree_info(t_tree *tree, t_tree_info *tr_info);
void	reset_tree_info(t_tree_info *info);
void	free_subtree(t_subtree *sbtr);
//pipe.c
void	my_dup2(t_subtree *subtree, int rd, int wr);
int		get_pipe_num_from_tree(t_tree *tre);
void	open_pipes(int num, int ***pipe_fd_tab);
void	close_all_pipe(int size, int **pipe_tab);
//subtree.c
int		make_subtree_lst(t_tree *tree, t_tree_info *info, t_dq *env);
//fd.c
int		open_infile_n_return(t_subtree *subtree);
int		open_outfile_n_return(t_subtree *subtree);
int		open_appending_n_return(t_subtree *subtree);
//file.c
int		get_infile_fd(t_subtree *subtree);
int		get_outfile_fd(t_subtree *subtree);
int		get_infile(t_tree *tree, t_subtree *new, t_dq *env);
int		get_outfile(t_tree *tree, t_subtree *new, t_dq *env);
//exec.c
int		exec_tree(t_tree *tree, t_dq *env);
//exec_subtree.c
void	redirection(t_subtree *subtree, int *stdin_copy, int *stdout_copy);
//handle_signal.c
void	handle_int_to_put_mark(int signum);
void	handle_int(int signum);
void	set_signal(struct sigaction *sa_int, struct sigaction *sa_quit);
void	handle_sigint_to_rl_restart(int signum);
//path.c
int		get_path(char **cmd, t_dq *env);
//envp.c
void	make_my_env(char **e, t_dq *env);
char	**get_envtab(t_dq *env);
//utils.c
char	*get_nth_token_from_lst(t_tree *tree, int nth);
char	**get_opt_from_lst(t_tree *tree);
void	free_tab(char **tab);
void	update_prev_status(t_dq *env);
void	perror_n_exit(const char *str);
//buf.c
int		check_buf(char **buf, t_dq *env);
//syntax.c
int		check_syntax_err(char *s, int *heredoc);
//heredoc.c
void	free_heredoc(char *buf, char *bkup, char *filename);
int		end_heredoc(char *buf, char *bkup, char *filename, int fd);
void	make_bkup(char *buf, char **bkup);
int		is_file_exist(char *filename, char *buf, char *bkup);
//heredoc2.c
int		write_line(char *filename, int heredoc_fd, char *limiter, int size);
int		write_heredoc(t_subtree *subtree);
//err.c
int		put_errmsg_syntax_err(t_tree *tree);
int		is_file_err(t_tree *tree, t_subtree *new, t_dq *env, int ret);
int		put_syntax_err_msg(char *s, int idx, int heredoc);
int		put_command_not_found(char *cmd);
//wait.c
void	wait_childs(t_tree_info *info, t_dq *env);
//builtins
int		_echo(t_subtree *t_subtree);
int		_cd(char *path, t_dq *env);
int		_pwd(void);
int		_export(char **opt, t_dq *env);
int		_unset(char **opt, t_dq *env);
int		_env(t_dq *env);
int		_exit_(char **opt);
int		_bexit_(char **opt, t_dq *env);
int		go_builtin(t_subtree *subtree, t_dq *env);
int		is_builtin(t_subtree *subtree);
int		b_redirection(t_subtree *subtree, int *stdin_copy, int *stdout_copy);
int		b_get_infile_fd(t_subtree *subtree);
int		b_get_outfile_fd(t_subtree *subtree);
#endif
