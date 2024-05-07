/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnavarre <vnavarre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 12:06:28 by ademaill          #+#    #+#             */
/*   Updated: 2024/05/07 13:40:28 by vnavarre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <unistd.h>
#include "../minishell.h"

int	g_pid = 0;

void	handler_signals(int sign)
{
	if (g_pid)
		return ;
	if (sign == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		//minishell_loop();
	}
}

static char	*ft_get_prompt(void)
{
	char	*tmp_pwd;
	char	*prompt;

	tmp_pwd = NULL;
	prompt = NULL;
	tmp_pwd = getcwd(tmp_pwd, 0);
	tmp_pwd = ft_strjoin(tmp_pwd, "$ ");
	if (!tmp_pwd)
		return (NULL);
	prompt = ft_strjoin("Minishell-ademaill-vnavarre", tmp_pwd);
	free(tmp_pwd);
	return (prompt);
}

void	minishell_loop(t_main *main)
{
	char	*buffer;
	char	*prompt;
	t_token	*tokens;
	g_pid = 0;

	tokens = NULL;
	main->env = ft_env_int(main->envp);
	while (1)
	{
		main->token = tokens;
		signal(SIGINT, handler_signals);
		signal(SIGQUIT, SIG_IGN);
		prompt = ft_get_prompt();
		buffer = readline(prompt);
		if (buffer == NULL)
		{
			ft_exit(main->token);
		}
		if (buffer)
			add_history(buffer);
		free(prompt);
		if (ft_strncmp(buffer, "exit", 5) == 0)
		{
			ft_exit(main->token);
			return ;
		}
		main->token = ft_tokenizer(buffer, main);
		t_token	*arr;
		int	i;
		int	j;
		j= 0;
		i = 0;
		arr = main->token;
		while (arr)
		{
			printf("token numero %d\n", i);
			i++;
			j = 0;
			while (arr->value[j])
			{
				printf("%s\n", arr->value[j]);
				j++;
			}
			//printf("%d\ng\n", tokens->type);
			if (arr->type == 0)
				printf("type : _cmdgrp\n\n");
			else if (arr->type == 1)
				printf("type : _pipe\n\n");
			else if (arr->type == 2)
				printf("type : _redirect_in\n\n");
			else if (arr->type == 3)
				printf("type : _redirect_out\n\n");
			else if (arr->type == 4)
				printf("type : _here_doc\n\n");
			else if (arr->type == 5)
				printf("type : _append\n\n");
			arr = arr->next;
		}
		free(main->token);
		//minishell_loop(main);
	}
}

int	main(int ac, char **av, char **envp)
{
	t_main	*main;

	(void)ac;
	(void)av;
	main = malloc(sizeof(t_main));
	main->envp = envp;
	minishell_loop(main);
	return (0);
}

