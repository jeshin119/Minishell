NAME = minishell
CC = cc
RM = rm -f
CFLAGS = -Wall -Wextra -Werror
DBGFLGS = -g -fsanitize=address
INCLUDE = ./include

LIBFT = ./libft/libft.a
PARSE_SRCS := parse/add_env_lset.c\
				parse/chk_ambi.c\
				parse/env_empty_chk.c\
				parse/env_len_chk.c\
				parse/env_string_chk.c\
				parse/env_utils.c\
				parse/env_utils_2.c\
				parse/free.c\
				parse/free_utils.c\
				parse/initilize.c\
				parse/make_node.c\
				parse/make_tree.c\
				parse/mallocs.c\
				parse/meta_characters.c\
				parse/my_deque.c\
				parse/my_deque2.c\
				parse/tk_list_chk.c\
				parse/token_split.c\
				parse/token_utils.c\
				parse/tokenize.c\
				parse/tree_utils.c
BUILTINS_SRCS := builtins/builtins.c\
					builtins/cd.c\
					builtins/echo.c\
					builtins/env.c\
					builtins/exit.c\
					builtins/export.c\
					builtins/prt_export.c\
					builtins/pwd.c\
					builtins/unset.c\
					builtins/b_utils.c
EXEC_SRCS := exec/buf.c\
				exec/buf_utils.c\
				exec/envp.c\
				exec/err.c\
				exec/errmsg.c\
				exec/exec.c\
				exec/exec_cmd.c\
				exec/fd.c\
				exec/handle_signal.c\
				exec/heredoc.c\
				exec/heredoc_utils.c\
				exec/path.c\
				exec/pipe.c\
				exec/redirection.c\
				exec/subtree.c\
				exec/subtree_list.c\
				exec/subtree_utils.c\
				exec/syntax.c\
				exec/tree_info.c\
				exec/utils.c\
				exec/wait.c
  
SRC = main.c $(PARSE_SRCS) $(BUILTINS_SRCS) $(EXEC_SRCS)
OBJ = $(SRC:.c=.o)

all : $(NAME)

%.c : %.o

$(NAME) : $(OBJ) $(LIBFT)
	@$(CC) $(CFLAGS) $(LIBFT) -l readline $^ -o $(NAME)
	@echo "minishell made"

%.o : %.c
	@$(CC) $(CFLAGS) -c $< -o $@

d : $(LIBFT) $(SRC)
	$(CC) $(CFLAGS) -lreadline $(DBGFLGS)  $(LIBFT) $(SRC) -o $(NAME)

$(LIBFT) : 
	@$(MAKE) -C ./libft
	@$(MAKE) bonus -C ./libft

clean :
	@$(RM) $(OBJ)
	@$(MAKE) clean -C libft

fclean : clean
	@$(RM) $(NAME)
	@$(MAKE) fclean -C libft

re : fclean all