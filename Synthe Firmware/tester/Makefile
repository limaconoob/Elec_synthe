MAKE = make
CC = gcc
RM = rm -f
CFLAGS = -Wall -Werror -Wextra
CPPFLAGS = -I./

NAME = synthe

SRC = main.c \
	  ft_concat.c \
	  ft_splitspaces.c \
	  get_next_line.c \
	  print_period.c \
	  regprocess.c \
	  tab_create.c \
	  tab_size.c

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	@$(CC) $(CPPFLAGS) $(OBJ) libft.a -o $(NAME)

$(OBJ):
	@$(CC) $(CPPFLAGS) $(SRC) -c

clean:
	@$(RM) $(OBJ)

fclean: clean
	@$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
