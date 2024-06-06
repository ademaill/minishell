/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademaill <ademaill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 11:36:21 by vnavarre          #+#    #+#             */
/*   Updated: 2024/06/06 17:53:36 by ademaill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <stdio.h>
# include <sys/wait.h>
# include <stdbool.h>
# include <fcntl.h>
# include "../minishell.h"
# include "get_next_line/get_next_line.h"

typedef struct s_main	t_main;
typedef struct s_env	t_env;

void	exec_cmd(char **cmd, char **envp, t_main *main);
void	ft_error(char *str, int code, char *error);
int		open_file(char	*name, int i);
void	here_doc(char *limiter, t_main *main);
char	*rand_path(void);
t_token	*ft_find(t_token *token, int i);
int		do_in(t_token *token, t_main *main, bool *heredoc);
int		do_out(t_token *token);
int		ft_cd(char **path, t_main *main);
int		ft_unset(char **av, t_main *main);
int		ft_echo(char **av);
void	ft_env(t_env *env);
int		ft_export(char **av, t_main *main);
int		ft_pwd(void);
int		ft_exit(t_main *main, char **value);
char	*clean_str(char *str);
void	ft_process(t_token *token, t_main *main, int *fd, bool last);
char	*f_path(char *cmd, char **envp);

#endif
