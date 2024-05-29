NAME = minishell
CC = cc
RM = rm -f
CFLAGS = -Wall -Wextra -Werror
DBGFLGS = -g -fsanitize=address
INCLUDE = ./include

LIBFT = ./libft/libft.a
SRC_DIRS = parse\
			 builtins\
			 exec
SRC = $(wildcard $(addsuffix /*.c , $(SRC_DIRS)))\
		 main.c

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