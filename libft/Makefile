NAME = libft.a

CC = cc
CFLAGS = -Wall -Wextra -Werror

AR = ar
ARFLAGS = crus

RM = rm -f

SRCS_FILES = ft_isalpha.c\
				ft_isdigit.c\
				ft_atoi.c\
				ft_atol.c\
				ft_bzero.c\
				ft_calloc.c\
				ft_isalnum.c\
				ft_isalpha.c\
				ft_isascii.c\
				ft_isdigit.c\
				ft_isprint.c\
				ft_isspace.c\
				ft_itoa.c\
				ft_memchr.c\
				ft_memcmp.c\
				ft_memcpy.c\
				ft_memmove.c\
				ft_memset.c\
				ft_putchar_fd.c\
				ft_putendl_fd.c\
				ft_putnbr_fd.c\
				ft_putstr_fd.c\
				ft_putaddr_fd.c\
				ft_puthex_fd.c\
				ft_split.c\
				ft_strchr.c\
				ft_strdup.c\
				ft_striteri.c\
				ft_strjoin.c\
				ft_strlcat.c\
				ft_strlcpy.c\
				ft_strlen.c\
				ft_strmapi.c\
				ft_strncmp.c\
				ft_strnstr.c\
				ft_strrchr.c\
				ft_strtrim.c\
				ft_substr.c\
				ft_tolower.c\
				ft_toupper.c\
				get_next_line.c\

BONUS_FILES = ft_lstadd_back.c\
				ft_lstadd_front.c\
				ft_lstlast.c\
				ft_lstnew.c\
				ft_lstsize.c\
				ft_lstdelone.c

SRCS = $(SRCS_FILES)
SRCS_BONUS = $(BONUS_FILES)

OBJS = $(SRCS:.c=.o)
	OBJS_BONUS = $(SRCS_BONUS:.c=.o)

all : $(NAME) 

$(NAME) : $(OBJS)
	@$(AR) $(ARFLAGS) $(NAME) $(OBJS)
	@echo "libft.a made"

bonus : $(OBJS) $(OBJS_BONUS)
	@$(AR) $(ARFLAGS) $(NAME) $(OBJS) $(OBJS_BONUS)
	@touch bonus
	@echo "libft.a bonus made"

%.o : %.c
	@$(CC) $(CFLAGS) -c $< -o $@

clean :
	@$(RM) $(OBJS) $(OBJS_BONUS) bonus

fclean : clean
	@$(RM) $(NAME)

re : fclean all

.PHONY = all clean fclean re