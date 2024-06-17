/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnavarre <vnavarre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 11:36:21 by vnavarre          #+#    #+#             */
/*   Updated: 2024/06/13 14:19:07 by vnavarre         ###   ########.fr       */
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

typedef struct s_main	t_main;
typedef struct s_env	t_env;

void	exec_cmd(char **cmd, char **envp, t_main *main);
void	ft_error(char *str, int code, char *error, t_main *main);
int		open_file(char	*name, int i, t_main *main);
void	here_doc(char *limiter, t_main *main);
char	*rand_path(t_main *main);
t_token	*ft_find(t_token *token, bool last, int pipecount);
t_token	*ft_find_cmdgr(t_token *token);
int		do_in(t_token *token, t_main *main, bool *heredoc);
int		do_out(t_token *token, t_main *main);
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
void	close_all(t_main *main);
void	end_of_while(int fd, char *line, char *tmp);
void	core_while(int fd, t_main *main, char *tmp, char *line);
void	else_pipex(bool last, t_main *main, t_token *token, pid_t rd);
void	close_process(t_main *main);
int		do_redirect_out(int out, char *path, t_token *tmp, t_main *main);

#endif
