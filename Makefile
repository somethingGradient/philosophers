# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: akitty <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/06/26 16:30:11 by akitty            #+#    #+#              #
#    Updated: 2022/06/26 16:30:12 by akitty           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	philo

INCLUDES	=	-pthread

HEADER		=	philo.h

CC			=	gcc

FLAGS		=	-Wall -Wextra -Werror

SRC			=	main.c life_conditions.c prepare_dinner.c \
				utils.c libft_utils.c  \

OBJ		=	$(SRC:.c=.o)

.SILENT: all clean fclean re

all: $(NAME)

$(NAME): $(OBJ) $(HEADER)
		@$(CC) $(FLAGS) -g $(OBJ) $(INCLUDES) -o $(NAME)
		@echo Compiled!  #-fsanitize=thread
	

%.o: %.c $(HEADER)
		@$(CC) -c -o $@ $< $(CPPFLAGS)

clean:
		@rm -rf $(OBJ)
		@echo Cleaned!
		
fclean: clean
		@rm -rf $(NAME)
		@echo Full cleaned!

re: fclean all

.PHONY: all clean fclean re
