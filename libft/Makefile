# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: akitty <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/10/22 16:11:11 by akitty            #+#    #+#              #
#    Updated: 2021/10/22 16:11:13 by akitty           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= libft.a

FT_H		= -I libft.h

FLAGS		= -Wall -Wextra -Werror

SRCS		= ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c \
ft_isprint.c ft_strlen.c ft_memset.c ft_bzero.c ft_memcpy.c \
ft_memmove.c ft_strlcpy.c ft_strlcat.c ft_toupper.c ft_tolower.c \
ft_strchr.c ft_strrchr.c ft_strncmp.c ft_memchr.c ft_memcmp.c \
ft_strnstr.c ft_atoi.c ft_calloc.c ft_strdup.c \
ft_substr.c ft_strjoin.c ft_strtrim.c ft_split.c ft_itoa.c \
ft_strmapi.c ft_striteri.c ft_putchar_fd.c ft_putstr_fd.c \
ft_putendl_fd.c ft_putnbr_fd.c ft_memccpy.c \
ft_atol.c ft_strcmp.c 

BONUS_SRCS	= ft_lstnew.c ft_lstadd_front.c ft_lstsize.c ft_lstlast.c \
ft_lstadd_back.c ft_lstdelone.c ft_lstiter.c

OBJ			= ${SRCS:.c=.o}
BONUS_OBJ	= ${BONUS_SRCS:.c=.o}

$(NAME):	${OBJ}
				@ar rcs $(NAME) ${OBJ}

%.o : 		%.c
				@gcc $(FLAGS) -c $< -o ${<:.c=.o}

all :		$(NAME)

bonus :		${NAME} ${OBJ} ${BONUS_OBJ}
				@ar rcs $(NAME) ${OBJ} ${BONUS_OBJ}

clean :
				@rm -f $(OBJ) $(BONUS_OBJ)

fclean : 	clean
				@rm -f $(NAME)

re :		fclean all

.PHONY:		all clean fclean re bonus
