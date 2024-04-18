NAME = minishell
CC = cc
SRCS = exec/pipex.c \
		exec/utils.c \
		exec/here_doc.c \
		exec/here_doc_utils.c \
		exec/get_next_line/get_next_line.c \
		lexer/lexer.c \
		prompt/prompt.c

HEADERS = minishell.h
OBJS = $(SRCS:.c=.o)
CFLAGS = -Wall -Wextra -Werror -g -lreadline
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
