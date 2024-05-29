/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeshin <jeshin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 17:45:24 by seunghan          #+#    #+#             */
/*   Updated: 2024/05/29 15:27:48 by jeshin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# define BACK_SLASH 1
# define ADD 1
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
	int					is_ambiguous;
	char				*infile;
	char				*no_infile;
	char				*outfile;
	char				*cmd;
	char				**opt;
	int					opt_size;
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
	char				**buf;
}	t_tree_info;

int		g_status;

//parse
void	meta_split(char *s, t_list **tk_list, int *i);
void	preorder_travel(t_tree *now, t_list *tk_list, t_node *env_list);
void	free_all(t_tree *tree, t_list *tk_list);
void	free_tk_idx_set(t_tree *tree);
void	free_next_node(t_tree *tree);
void	go_to_first(t_tree **tree, t_list **tk_list);
void	alloc_env_len(t_env *env_lset_new, char *s, int e_idx, int i);
void	handle_qt(t_env *env_lset, int e_idx, int q_flag, int hd_flag);
void	ini_q_flag_idx(int *q_flag, int *i);
void	env_white_chk(t_list *tk_list, t_node *env_list);
void	chk_ambi(t_list *tkl, t_list *tmp_tkl, t_node *env_list, char *cl);
void	ini_tree_node(t_tree *next, t_list *tk_list_arg);
void	token_merge(t_list *tk_list, char *str, int start, int len);
void	put_str_in_tk_list(t_list *tk_list, char *str, int start, int len);
void	add_env_lset(t_list *tk_list, t_env *env_lset_arg);
int		pipe_chk(t_list *tk_list);
int		meta_chk(char *s, int i, int meta_value);
int		white_chk(char ch);
int		right_rd_chk(t_list *tk_list);
int		quote_closed_chk(char *s, int i);
int		get_double_direct(int direct);
int		env_count_chk(char *s);
int		env_name_len_chk(char *s, int *i);
int		env_first_ch_chk(char *s, int i);
int		name_valid_chk(char *name, char *s, int i);
int		add_input(t_tree_info *info, t_tree *now, t_list *tkl, t_node *env);
int		contain_quote_tmp(t_list *tk_list, int *start);
char	*get_front_str(char *token, char *s, int i, int *front_len);
char	*malloc_readline(char *buf);
char	*env_string_chk(char *input, t_node *env_list, int hd_flag);
char	*env_len_and_empty(t_list *tk_list, char *token, int meta_value);
char	*empty_fenv(char *str);
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
t_tree	*parse(char *line, t_dq *env);
t_list	*tokenize(char *cmd_line, int add, t_node *env_list);
t_list	*token_split(t_list *tk_list, char *s, int tmp_flag);
t_list	*mv_to_valid_token(t_tree *now, int i);
t_node	*chk_valid_env(t_tree *now, char *s, int i, t_node *env_list);
t_node	*env_name_chk(char *s, t_node *env_list, int i);
t_node	*chk_env(t_env *env_lset, char *s, int i, t_node *env_list);
t_env	*ini_env_lset(t_env *env_lset_new, int env_cnt);
t_env	*env_len_chk(char *input, int hd_flag);

//////////////////////////////////////////////////////////////
//exec part
//exec.c
int		exec_tree(char **buf, t_tree *tree, t_dq *env);
//exec_cmds.c
void	exec_cmds(t_tree_info *tree_info, t_dq *env);
//////////////////////////////////////////////////////////////
//subtree for exec tree
//subtree_list.c
int		make_subtree_list(t_tree *tree, t_tree_info *info, t_dq *env);
//subtree.c
void	init_subtree(t_subtree **subtree);
int		create_subtree(t_tree *tree, t_subtree **new, t_dq *env);
int		link_subtree(t_sbt_lst **sbtr_lst, t_subtree *new);
//subtree_utils.c
int		get_infile(t_tree *tree, t_subtree **new, t_dq *env);
int		get_outfile(t_tree *tree, t_subtree **new);
int		get_cmd_opt(t_tree *tree, t_subtree **new);
//////////////////////////////////////////////////////////////
//tree_info
//tree_info.c
void	init_tree_info(char **buf, t_tree *tree, t_tree_info *tree_info);
void	reset_tree_info(t_tree_info *info);
int		free_subtree(t_subtree **sbtr);
//////////////////////////////////////////////////////////////
//redirection
//redicrection.c
void	save_stdin_stdout(t_subtree *sbtr, int *stdin_copy, int *stdout_copy);
int		redirection(t_subtree *subtree, int *stdin_copy, int *stdout_copy);
void	get_back_redirection(t_subtree *sbte, int stdin_copy, int stdout_copy);
//pipe.c
void	my_dup2(t_subtree *subtree, int rd, int wr);
int		get_pipe_num_from_tree(t_tree *tre);
void	open_pipes(int num, int ***pipe_fd_tab);
void	close_all_pipe(int size, int **pipe_tab);
//////////////////////////////////////////////////////////////
//fd.c
int		open_infile(t_subtree *subtree);
int		open_outfile(t_subtree *subtree, int is_appending);
int		open_tmp_outfile(char *tmp, int is_appending);
int		get_infile_fd(t_subtree *subtree);
int		get_outfile_fd(t_subtree *subtree);
//////////////////////////////////////////////////////////////
//heredoc
//heredoc.c
int		get_heredoc(t_tree *tree, t_subtree *subtree, t_dq *env);
//heredoc_utils.c
void	check_already_has_heredoc(t_subtree *new);
int		free_heredoc(char *buf, char *filename);
int		exist_file(char *filename);
//////////////////////////////////////////////////////////////
//handle signal
//handle_signal.c
void	handle_sigint_in_main(int signum);
void	handle_sigint_to_exit_readline(int signum);
void	set_signal_in_main(void);
void	set_signal_in_exec(void);
//////////////////////////////////////////////////////////////
//path for execve
//path.c
int		get_path(char **cmd, t_dq *env);
//////////////////////////////////////////////////////////////
//env list and env arrary
//envp.c
void	make_my_env(char **e, t_dq *env);
char	**get_envtab(t_dq *env);
//////////////////////////////////////////////////////////////
//utils
//utils.c
char	*get_nth_token_from_lst(t_tree *tree, int nth);
int		get_opt_from_lst(t_tree *tree, t_subtree **new);
void	free_tab(char **tab, int size);
void	update_prev_status(t_dq *env);
void	perror_n_exit(const char *str);
//////////////////////////////////////////////////////////////
//manage readline_buf
//buf.c
int		check_buf(char **buf);
int		check_extra_buf(char **bkup, char **buf);
//buf_utils.c
int		is_ended_with_pipe(char *buf);
int		is_empty(char *buf);
int		get_extra_buf(char **buf);
int		exit_when_eof(void);
//syntax.c
int		check_buf_syntax_err(char *s, int *heredoc);
//////////////////////////////////////////////////////////////
//err
//err.c
int		check_subtree_syntax_err(t_tree *tree, t_subtree **new);
int		check_ambiguous(t_tree *tree, t_subtree *subtree);
int		is_subtree_ambiguous(t_subtree *subtree);
int		has_subtree_no_infile(t_subtree *subtree);
//errmsg.c
int		put_subtree_has_syntax_err_msg(t_tree *tree);
int		put_subtree_has_nofile_err_msg(t_subtree *subtree);
int		put_buf_has_syntax_err_msg(char *s, int idx, int heredoc);
int		put_command_not_found(char *cmd);
//////////////////////////////////////////////////////////////
//wait child
//wait.c
void	wait_childs(t_tree_info *info, t_dq *env);
//////////////////////////////////////////////////////////////
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
//////////////////////////////////////////////////////////////
#endif
