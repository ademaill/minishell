/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademaill <ademaill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 15:46:21 by vnavarre          #+#    #+#             */
/*   Updated: 2024/06/06 20:01:39 by ademaill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	g_sig_received;

static void	status_exit(t_main *main, int pid, bool last)
{
	int	status;

	status = 0;
	if (pid > 0)
	{
		if (g_sig_received)
			kill(pid, g_sig_received);
		waitpid(pid, &status, 0);
		if (WTERMSIG(status) == SIGQUIT)
		{
			main->exit_code = 131;
			if (last)
				ft_putstr_fd(" Quit (Core dumped)\n", 2);
		}
		if (WIFEXITED(status))
			main->exit_code = WEXITSTATUS(status);
	}
	if (pid == -42)
		main->exit_code = EXIT_FAILURE;
}

static char	*ft_get_prompt(t_env *env)
{
	char	*tmp_pwd;
	t_env	*tmp;
	char	*prompt;
	char	*tmp_pwd2;

	tmp = env;
	tmp_pwd = NULL;
	tmp_pwd2 = NULL;
	prompt = NULL;
	while (tmp)
	{
		if (ft_strncmp(tmp->key, "PWD", 4) == 0)
			break ;
		tmp = tmp->next;
	}
	if (tmp && tmp->value)
		tmp_pwd2 = ft_strdup(tmp->value);
	else
		tmp_pwd2 = ft_strdup("");
	tmp_pwd = ft_strjoin(tmp_pwd2, "$ ", false);
		free(tmp_pwd2);
	if (!tmp_pwd)
		return (NULL);
	prompt = ft_strjoin("Minishell-ademaill-vnavarre", tmp_pwd, false);
	free(tmp_pwd);
	return (prompt);
}

static void	exec_and_free(t_main *main)
{
	int		i;
	t_token	*tmp;
	bool	last;

	i = 0;
	if (!main->token)
		minishell_loop(main);
	ft_exec(main);
	last = false;
	while (main->pid[i])
	{
		if (!main->pid[i + 1])
			last = true;
		status_exit(main, main->pid[i], last);
		i++;
	}
	free(main->pid);
	i = 0;
	while (main->token)
	{
		tmp = main->token;
		main->token = main->token->next;
		free_tab(tmp->value);
		free(tmp);
	}
}

void	minishell_loop(t_main *main)
{
	char	*buffer;
	char	*prompt;

	while (1)
	{
		main->token = NULL;
		prompt = ft_get_prompt(main->env);
		buffer = readline(prompt);
		if (g_sig_received == SIGINT)
		{
			main->exit_code = 130;
			g_sig_received = 0;
		}
		if (buffer == NULL)
			ft_fullexit(main->token, prompt);
		if (buffer && buffer[0] != '\0')
			add_history(buffer);
		free(prompt);
		main->token = ft_tokenizer(buffer, main);
		buffer = NULL;
		exec_and_free(main);
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
	if (!envp[0])
		data->envp = NULL;
	data->envp = envp;
	data->env = ft_env_int(data->envp);
	ft_got_signal(1);
	minishell_loop(data);
	free(data);
	return (0);
}

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
