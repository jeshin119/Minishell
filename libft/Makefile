# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    MAKEFILE                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: seunghan <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/11 11:32:36 by seunghan          #+#    #+#              #
#    Updated: 2024/04/08 15:19:41 by seunghan         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CFLAGS = -Wall -Wextra -Werror
NAME = libft.a
SRCS = ft_strlen.c\
	   ft_strncmp.c\
	   ft_strdup.c\
	   ft_substr.c\
	   ft_strjoin.c\
	   ft_strtrim.c\
	   ft_split.c\
	   ft_putchar_fd.c\
	   ft_putstr_fd.c\
	   ft_putendl_fd.c\
	   ft_putnbr_fd.c
BSRC = ft_lstnew.c\
	   ft_lstsize.c\
	   ft_lstlast.c\
OBJECTS = $(SRCS:.c=.o)
BONUSOB = $(BSRC:.c=.o)

ifdef WITH_BONUS
	OBJS = $(OBJECTS) $(BONUSOB)
else
	OBJS = $(OBJECTS)
endif

all : $(NAME)

$(NAME) : $(OBJS)
	ar -rc $@ $^

bonus :
	make WITH_BONUS=1 all

.c .o : $(OBJS)
	cc $(CFLAGS) -o $@ -c $^

clean :
	rm -rf $(OBJECTS) $(BONUSOB)

fclean : clean
	rm -rf $(NAME)

re : fclean all

.PHONY : all bonus clean fclean re
