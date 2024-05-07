NAME = minishell
CC = cc
SRCS = exec/pipex.c \
		exec/utils.c \
		exec/here_doc.c \
		exec/here_doc_utils.c \
		exec/get_next_line/get_next_line.c \
		exec/get_next_line/get_next_line_utils.c \
		lexer/lexer.c \
		builtins/env_utils.c \
		builtins/ft_cd.c \
		builtins/ft_echo.c \
		builtins/ft_env.c \
		builtins/ft_export.c \
		builtins/ft_pwd.c \
		builtins/ft_unset.c \
		builtins/utils.c \
		expand/expand_utils.c \
		expand/expand.c \
		prompt/prompt.c \
		prompt/utils_prompt.c \
		parsing/parse_pipe.c \
		parsing/parse_utils.c

HEADERS = minishell.h
OBJS = $(SRCS:.c=.o)
CFLAGS = -Wall -Wextra -Werror -g
LIBFT = Libft/libft.a
LIBFT_PATH = "Libft"
READLINE_PATH:=	/goinfre/homebrew/opt/readline

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	$(CC) -o $(NAME) -L$(LIBFT_PATH) -lft -L$(READLINE_PATH)/lib -lreadline $@ $^

%.o: %.c $(HEADER)
	$(CC) $(CFLAGS) -c $< -o $@ -Iinclude -I$(READLINE_PATH)/include

$(LIBFT):
	@make -C $(LIBFT_PATH)
	@make bonus -C $(LIBFT_PATH)

fclean: clean
	@make fclean -C $(LIBFT_PATH)
	rm -f $(NAME)

clean:
	@make clean -C $(LIBFT_PATH)
	rm -f $(OBJS)


re: fclean all

.PHONY: all fclean clean re
