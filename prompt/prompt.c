/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnavarre <vnavarre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 15:46:21 by vnavarre          #+#    #+#             */
/*   Updated: 2024/06/17 14:36:14 by vnavarre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

static void	ft_get_prompt(t_env *env, char **prompt)
{
	char	*tmp_pwd;
	t_env	*tmp;
	char	*tmp_pwd2;

	tmp = env;
	tmp_pwd = NULL;
	tmp_pwd2 = NULL;
	while (tmp)
	{
		if (ft_strncmp(tmp->key, "PWD", 3) == 0)
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
		*prompt = NULL;
	*prompt = ft_strjoin("Minishell-ademaill-vnavarre", tmp_pwd, false);
	free(tmp_pwd);
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
	while (main->pid && main->pid[i])
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

static void	error_quotes(char *str, t_main *main)
{
	int	i;
	int	stat;
	int	sq;
	int	dq;

	i = 0;
	sq = 0;
	dq = 0;
	while (str[i] && str[i] != '\'' && str[i] != '"')
		i++;
	stat = i;
	while (str[i])
	{
		if (str[stat] == '"' && str[i] == '"')
			dq++;
		if (str[stat] == '\'' && str[i] == '\'')
			sq++;
		i++;
	}
	if (dq % 2 != 0 || sq % 2 != 0)
	{
		free(str);
		ft_putstr_fd("Quotes unclosed\n", 2);
		minishell_loop(main);
	}
}

void	minishell_loop(t_main *main)
{
	char	*buffer;
	char	*prompt;

	while (1)
	{
		//main->envp = t_env_to_strtab(main->env);
		main->token = NULL;
		ft_get_prompt(main->env, &prompt);
		buffer = readline(prompt);
		free(prompt);
		if (buffer == NULL)
			buffer = ft_strdup("exit");
		if (g_sig_received == SIGINT)
		{
			main->exit_code = 130;
			g_sig_received = 0;
		}
		error_quotes(buffer, main);
		if (buffer && buffer[0] != '\0')
			add_history(buffer);
		main->token = ft_tokenizer(buffer, main);
		buffer = NULL;
		exec_and_free(main);
		free(main->token);
	}
}
