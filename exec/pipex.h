/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnavarre <vnavarre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 11:36:21 by vnavarre          #+#    #+#             */
/*   Updated: 2024/04/17 10:34:33 by vnavarre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <stdio.h>
# include <sys/wait.h>
# include <fcntl.h>
# include "../minishell.h"
# include "get_next_line/get_next_line.h"

void	exec_cmd(char *av, char **envp);
void	ft_error(void);
int		open_file(char	*name, int i);
char	*here_doc(char *limiter);
char	*rand_path(void);

#endif
