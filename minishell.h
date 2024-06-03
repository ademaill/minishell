/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnavarre <vnavarre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 15:48:14 by ademaill          #+#    #+#             */
/*   Updated: 2024/06/03 12:08:34 by vnavarre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "lexer/lexer.h"
# include "Libft/libft.h"
# include "execution/pipex.h"
# include "parsing/parsing.h"
# include <stdlib.h>
# include <unistd.h>
# include <stdbool.h>
# include <signal.h>
# include <dirent.h>
#include <readline/readline.h>
#include <readline/history.h>

extern int	g_sig_received;

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}	t_env;

typedef struct s_main
{
	t_env	*env;
	t_token	*token;
	int		exit_code;
	int		pipe_count;
	int		*pid;
	char	**envp;
	char	*heredoc_path;
}	t_main;

void	*ft_garbage_collector(void *ptr, bool clean);
void	ft_update(char *key, char *value, t_env *env, bool c);
char	*ft_key(char *str);
char	*ft_value(char *str);
t_env	*ft_lst_env_new(char *key, char *value);
void	ft_lstadd_back_env(t_env **lst, t_env *new);
t_env	*ft_env_int(char **envp);
void	ft_env(t_env *env);
char	*ft_get_envlst_val(char *key, t_env *envlst);
int		check_key(char *str);
void	sort_lst(t_env **head);
bool	ft_env_exists(char *key, t_main *main);
char	*handle_next(int *i, char *tmp, char *str, t_main *main);
char	*ft_handle_dollars(char *str, int *i, t_main *main);
char	*ft_handle_s_quotes(char *str, int *i, bool dquotes);
char	*ft_handle_d_quotes(char *str, int *i);
char	*ft_handle_str(char *str, int *i);
void	minishell_loop(t_main *main);
t_token	*ft_tokenizer(char *line, t_main *main);
void	ft_fullexit(t_token *token);
char	*ft_cmd_pre_expand(char *str, t_main *main);
int		ft_exec(t_main *main);
void	exec_builtins(t_token *token, t_main *main);
int		is_builtins(t_token *token);
char	*clean_str(char *str);
void	ft_got_signal(int handle);
void	free_all(t_main *main);

#endif
