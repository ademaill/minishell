NAME = pipex
CC = cc
SRCS = pipex.c utils.c here_doc.c here_doc_utils.c get_next_line/get_next_line.c
HEADERS = pipex.h
OBJS = $(SRCS:.c=.o)
CFLAGS = -Wall -Wextra -Werror -g
LIBFT = Libft/libft.a
LIBFT_PATH = "Libft"

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) -L$(LIBFT_PATH) -o $@ $^

$(LIBFT):
	@make -C $(LIBFT_PATH)
	@make bonus -C $(LIBFT_PATH)

%.o: %.c $(HEADER)
	$(CC) $(CFLAGS) $< -c -o $@


fclean: clean
	@make fclean -C $(LIBFT_PATH)
	rm -f $(NAME)

clean:
	@make clean -C $(LIBFT_PATH)
	rm -f $(OBJS)


re: fclean all

.PHONY: all fclean clean re
