# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mmedjahe <mmedjahe@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/16 17:32:22 by mmedjahe          #+#    #+#              #
#    Updated: 2025/07/18 00:09:49 by mmedjahe         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

CC = cc
FLAGS = -Wall -Wextra -Werror -fPIC
AR = ar
RM = rm -f

FILES = ft_strdup.c \
		ft_atoi.c \
		ft_bzero.c \
		ft_isalnum.c \
		ft_isalpha.c \
		ft_isascii.c \
		ft_isdigit.c \
		ft_isprint.c \
		ft_memchr.c \
		ft_memcmp.c \
		ft_memcpy.c \
		ft_memmove.c \
		ft_memset.c \
		ft_strchr.c \
		ft_strlcat.c \
		ft_strlcpy.c \
		ft_strlen.c \
		ft_strncmp.c \
		ft_strnstr.c \
		ft_strrchr.c \
		ft_tolower.c \
		ft_toupper.c \
		ft_calloc.c \
		ft_putstr_fd.c \
		ft_putchar_fd.c \
		ft_itoa.c \
		ft_putnbr_fd.c \
		ft_substr.c \
		ft_putendl_fd.c \
		ft_strmapi.c \
		ft_strtrim.c \
		ft_striteri.c \
		ft_strjoin.c \
		ft_split.c \
		ft_lstnew.c \
		ft_lstadd_front.c \
		ft_lstsize.c \
		ft_lstlast.c \
		ft_lstadd_back.c \
		ft_lstdelone.c \
		ft_lstclear.c \
		ft_lstiter.c \
		ft_lstmap.c \
		./printf/ft_printf.c \
		./printf/ft_print_c.c \
		./printf/ft_print_di.c \
		./printf/ft_print_formatted.c \
		./printf/ft_print_p.c \
		./printf/ft_print_s.c \
		./printf/ft_print_u.c \
		./printf/ft_print_x.c \
		./gnl/get_next_line.c\

OBJS = ${FILES:.c=.o}

.c.o:
	@printf "\r\033[K[libft] \033[0;32mCompilation : $<\033[0m"
	${CC} ${FLAGS} -c $< -o ${<:.c=.o}

$(NAME): $(OBJS)
	@printf "\r\033[K[libft] \033[0;32mLinking...\033[0m"
	$(AR) rc $(NAME) $(OBJS)
	@printf "\r\033[K[libft] \033[0;32mDone!\033[0m\n"

all: $(NAME)

clean:
	$(RM) $(OBJS) $(BOBJS)
	@printf "[libft] \033[1;31mCleaned .o!\033[0m\n"

fclean: clean
	$(RM) $(NAME)
	@printf "[libft] \033[1;31mCleaned all!\033[0m\n"
re: clean all

bonus: $(BOBJS)
	$(AR) rc $(NAME) $(BOBJS)

.PHONY: all clean fclean re bonus