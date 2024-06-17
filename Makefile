NAME = minishell
CC = cc
SRCS = main.c \
		execution/pipex.c \
		execution/pipex_utils.c \
		execution/utils.c \
		execution/redirection.c \
		execution/utils2.c \
		execution/here_doc.c \
		execution/here_doc_utils.c \
		execution/ft_find.c \
		execution/ft_process.c \
		execution/redirection_utils.c \
		lexer/lexer.c \
		lexer/lexer_utils.c \
		lexer/lexer_utils2.c \
		lexer/ft_split_ms.c \
		lexer/ft_cmd_type.c \
		builtins/env_utils.c \
		builtins/ft_cd.c \
		builtins/ft_echo.c \
		builtins/ft_env.c \
		builtins/ft_export.c \
		builtins/ft_pwd.c \
		builtins/ft_unset.c \
		builtins/ft_exit.c \
		builtins/ft_value.c \
		builtins/utils.c \
		builtins/ft_export_list.c \
		expand/expand_utils.c \
		expand/expand.c \
		parsing/clean_str.c \
		parsing/parse_pipe.c \
		parsing/parse_utils.c \
		prompt/prompt.c \
		prompt/signal.c


HEADERS = minishell.h
OBJS = $(SRCS:.c=.o)
CFLAGS = -Wall -Wextra -Werror -g
LIBFT = Libft/libft.a
LIBFT_PATH = "Libft"

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) -o $(NAME) -L$(LIBFT_PATH) $^ -o $@ -lreadline

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
