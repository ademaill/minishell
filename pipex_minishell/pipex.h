/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademaill <ademaill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 11:36:21 by vnavarre          #+#    #+#             */
/*   Updated: 2024/04/16 15:52:07 by ademaill         ###   ########.fr       */
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
void	here_doc(char *limiter);
char	*rand_path(void);

#endif
