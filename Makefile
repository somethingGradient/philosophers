NAME		=	philosophers

INCLUDES	=	-pthread

HEADER		=	philosophers.h

CC			=	gcc

FLAGS		=	-Wall -Wextra -Werror

SRC			=	main.c \
				check_args.c \

OBJ		=	$(SRC:.c=.o)

LIBFT_PATH	=	libft/

LIBFT		=	libft/libft.a

.SILENT: all clean fclean re

all: $(NAME)

$(NAME): $(OBJ) $(HEADER)
#@$(MAKE) all -C $(LIBFT_PATH)
		@$(CC) -g $(OBJ) $(LIBFT) $(INCLUDES) -o $(NAME)
#@echo Compiled!  -fsanitize=thread
	

%.o: %.c $(HEADER)
		@$(CC) -c -o $@ $< $(CPPFLAGS)

clean:
#@$(MAKE) clean -C $(dir $(LIBFT))
		@rm -rf $(OBJ)
#@echo Cleaned!
		
fclean: clean
		#@$(MAKE) fclean -C $(dir $(LIBFT))
		@rm -rf $(NAME)
		#@echo Full cleaned!

re: fclean all

.PHONY: all clean fclean re