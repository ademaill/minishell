/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnavarre <vnavarre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 15:46:21 by vnavarre          #+#    #+#             */
/*   Updated: 2024/05/31 18:32:03 by vnavarre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <unistd.h>
#include "../minishell.h"

static void	status_exit(t_main *main, int pid)
{
	int	status;

	status = 0;
	if (pid > 0)
	{
		//if (g_sig_received)
			//kill(pid, g_sig_received);
		waitpid(pid, &status, 0);
		if (WTERMSIG(status) == SIGQUIT)
			printf(" Quit (Core dumped)\n");
		if (WIFEXITED(status))
			main->exit_code = WEXITSTATUS(status);
	}
	//if (pid == -42)
		//main->exit_code = EXIT_FAILURE;
}

void	handler_signals(int sign)
{
	if (sign == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
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
	t_token	*tmp;
	int		i;

	while (1)
	{
		main->token = NULL;
		signal(SIGINT, handler_signals);
		signal(SIGQUIT, SIG_IGN);
		prompt = ft_get_prompt();
		buffer = readline(prompt);
		if (ft_strncmp(buffer, "", 1) == 0)
		{
			rl_on_new_line();
			rl_replace_line("", 0);
			rl_redisplay();
			minishell_loop(main);
		}
		if (buffer == NULL)
		{
			ft_fullexit(main->token);
		}
		if (buffer)
			add_history(buffer);
		free(prompt);
		main->token = ft_tokenizer(buffer, main);
		buffer = NULL;
		if (!main->token)
			minishell_loop(main);
		ft_exec(main);
		i = 0;
		while (main->pid[i])
		{
			status_exit(main, main->pid[i]);
			i++;
		}
		free(main->pid);
		/*t_token	*arr;
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
			if (arr->type == 0)
				printf("type : _redirect_in\n\n");
			else if (arr->type == 1)
				printf("type : _cmdgr\n\n");
			else if (arr->type == 2)
				printf("type : _pipe\n\n");
			else if (arr->type == 3)
				printf("type : _redirect_out\n\n");
			else if (arr->type == 4)
				printf("type : _here_doc\n\n");
			else if (arr->type == 5)
				printf("type : _append\n\n");
			arr = arr->next;
		}*/
		i = 0;
		while (main->token)
		{
			tmp = main->token;
			main->token = main->token->next;
			free_tab(tmp->value);
			free(tmp);
		}
		free(main->token);
	}
}

int	main(int ac, char **av, char **envp)
{
	t_main	*data;

	(void)ac;
	(void)av;
	data = malloc(sizeof(t_main));
	ft_memset(data, 0, sizeof(t_main));
	data->envp = envp;
	data->env = ft_env_int(data->envp);
	minishell_loop(data);
	free(data);
	return (0);
}
