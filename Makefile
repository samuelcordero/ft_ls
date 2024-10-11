LIBFT = libft/libft.a
LDFLAGS = -L libft -lft
NAME = ft_ls
CFLAGS = -Wall -Wextra -Werror -O3 -I incs -I libft #-g3 -fsanitize=address
SRC =	srcs/main.c \
		srcs/dir_lister.c	
OBJ = $(SRC:.c=.o)
RM=/bin/rm -f
CC = gcc

all: $(NAME)

$(LIBFT):
	@make bonus -C ./libft
	
$(NAME): $(LIBFT) $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(LDFLAGS) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	@make clean -C ./libft
	$(RM) $(OBJ)
	$(RM) $(OBJBONUS)

fclean: clean
	@make fclean -C ./libft
	$(RM) $(NAME)

re:: fclean
re:: all

asan:: CFLAGS += -fsanitize=address -g3
asan:: LDFLAGS += -fsanitize=address
asan:: re


normi:
	@norminette src inc libft

.PHONY: all clean fclean re normi
