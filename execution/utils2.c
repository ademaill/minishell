/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnavarre <vnavarre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 11:01:11 by vnavarre          #+#    #+#             */
/*   Updated: 2024/05/16 12:58:15 by vnavarre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	is_builtins(t_token *token)
{
	if (ft_strncmp(token->value[0], "pwd", 3) == 0)
		return (1);
	else if (ft_strncmp(token->value[0], "cd", 2) == 0)
		return (1);
	else if (ft_strncmp(token->value[0], "export", 6) == 0)
		return (1);
	else if (ft_strncmp(token->value[0], "env", 3) == 0)
		return (1);
	else if (ft_strncmp(token->value[0], "unset", 5) == 0)
		return (1);
	else if (ft_strncmp(token->value[0], "echo", 4) == 0)
		return (1);
	//else if (ft_strncmp(token->value[0], "exit", 5) == 0)
		//return (1);
	else
		return (0);
}

void	exec_builtins(t_token *token, t_main *main)
{
	if (ft_strncmp(token->value[0], "pwd", 3) == 0)
		ft_pwd();
	else if (ft_strncmp(token->value[0], "cd", 2) == 0)
		ft_cd(token->value[1], main->envp);
	else if (ft_strncmp(token->value[0], "export", 6) == 0)
		ft_export(token->value, main);
	else if (ft_strncmp(token->value[0], "echo", 4) == 0)
		ft_echo(token->value);
	else if (ft_strncmp(token->value[0], "unset", 5) == 0)
		ft_unset(token->value, main->envp);
	else if (ft_strncmp(token->value[0], "env", 3) == 0)
		ft_env(main->envp);
	//else if (ft_strncmp(token->value[0], "exit", 5) == 0)
		//ft_exit();
}
