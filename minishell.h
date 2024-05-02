/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnavarre <vnavarre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 15:48:14 by ademaill          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2024/05/01 16:30:48 by vnavarre         ###   ########.fr       */
=======
/*   Updated: 2024/04/23 13:06:58 by ademaill         ###   ########.fr       */
>>>>>>> 810fed111039ad2cbc8e6f61aec4b5e8e3a92fb4
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "lexer/lexer.h"
# include "Libft/libft.h"
# include "exec/pipex.h"
# include "parsing/parsing.h"
# include <stdlib.h>
# include <unistd.h>
<<<<<<< HEAD
# include <stdbool.h>

typedef struct s_env
{
	char		*key;
	char		*value;
	struct s_env	*next;
}	t_env;

void	*ft_garbage_collector(void *ptr, bool clean);
void	ft_update(char *key, char *value, t_env *env, bool c);
char	*ft_key(char *str);
char	*ft_value(char *str);
t_env	*ft_lst_env_new(char *key, char *value);
void	ft_lstadd_back_env(t_env **lst, t_env *new);
t_env	*ft_env_int(char **envp);
void	ft_env(char **envp);
char	*ft_get_envlst_val(char *key, t_env *envlst);
int		check_key(char *str);
void	sort_lst(t_env **head);
bool	ft_env_exists(char *key, char **envp);
char	*ft_handle_s_quotes(char *str, int *i);
char	*ft_handle_d_quotes(char *str, int *i);
char	*ft_handle_str(char *str, int *i);

=======
# include <signal.h>

void	minishell_loop(void);
void	handler_signals(int sign);
void	ft_exit(t_token *token);
>>>>>>> 810fed111039ad2cbc8e6f61aec4b5e8e3a92fb4

#endif
