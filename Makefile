NAME = minishell
CC = cc
RM = rm -f
# CFLAGS = -Wall -Wextra -Werror
DBGFLGS = -g -fsanitize=address
INCLUDE = ./include


LIBFT = ./libft/libft.a
SRC_DIRS = parse builtins pipex
SRC = $(wildcard $(addsuffix /*.c , $(SRC_DIRS)))
OBJ = $(SRC:.c=.o)

all : $(NAME)

%.c : %.o

$(NAME) : $(OBJ) $(LIBFT)
	@$(CC) $(CFLAGS) $(LIBFT) -l readline $^ -o $(NAME)
	@echo "minishell made"

%.o : %.c
	@$(CC) $(CFLAGS) -c $< -o $@

debug : $(LIBFT) $(OBJ)
	@$(CC) $(CFLAGS) -lreadline $(DBGFLGS) -o $(NAME)

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