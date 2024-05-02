/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademaill <ademaill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 12:06:28 by ademaill          #+#    #+#             */
/*   Updated: 2024/04/25 17:47:02 by ademaill         ###   ########.fr       */
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
	else if (sign == SIGQUIT)
	{
		//rl_on_new_line();
		//rl_redisplay();
		printf("  \b\b");
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

void	minishell_loop(void)
{
	char	*buffer;
	char	*prompt;
	t_token	*tokens;
	g_pid = 0;

	tokens = NULL;
	while (1)
	{
		signal(SIGINT, handler_signals);
		signal(SIGQUIT, SIG_IGN);
		prompt = ft_get_prompt();
		buffer = readline(prompt);
		if (buffer == NULL)
		{
			ft_exit(tokens);
		}
		if (buffer)
			add_history(buffer);
		free(prompt);
		if (ft_strncmp(buffer, "exit", 5) == 0)
		{
			ft_exit(tokens);
			return ;
		}
		tokens = ft_tokenizer(buffer);
		t_token	*arr;
		int	i;
		int	j;
		j= 0;
		i = 0;
		arr = tokens;
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
			if (arr->type == 0)
				printf("type : _cmdgrp\n\n");
			else if (arr->type == 1)
				printf("type : _pipe\n\n");
			else if (arr->type == 2)
				printf("type : _redirect\n\n");
			else if (arr->type == 3)
				printf("type : _var_env\n\n");
			else if (arr->type == 4)
				printf("type : _here_doc\n\n");
			else if (arr->type == 5)
				printf("type : _append\n\n");
			arr = arr->next;
		}
	}
}

int	main(void)
{
	minishell_loop();
	return (0);
}
