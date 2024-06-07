/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnavarre <vnavarre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 09:05:06 by vnavarre          #+#    #+#             */
/*   Updated: 2024/06/07 14:00:28 by vnavarre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	handle_signal_here_doc(int sgn)
{
	g_sig_received = sgn;
	//(void)sgn;
	close(STDIN_FILENO);
}

void	handle_signal_here(int sgn)
{
	g_sig_received = sgn;
	if (sgn == SIGQUIT)
	{
		printf("\n");
		exit (1);
	}
	if (sgn == 0)
	{
		printf("\n");
		exit (1);
	}
}

static char	*ft_expand_here_doc(char *str, t_main *main)
{
	char	*ret ;
	int		i;

	i = 0;
	ret = ft_strdup("");
	while (str[i])
	{
		if (str[i] == '$')
			ret = ft_strjoin(ret, ft_handle_dollars(str, &i, main), true);
		else if (str[i] == '"')
			ret = ft_strjoin(ret, ft_handle_d_quotes(str, &i, true), true);
		else if (str[i] == '\'')
			ret = ft_strjoin(ret, ft_handle_s_quotes(str, &i, true), true);
		else
			ret = ft_strjoin(ret, ft_handle_str(str, &i), true);
	}
	free(str);
	return (ret);
}

static char	*while_here_doc(t_main *main, char *limiter, int fd)
{
	char	*line;
	char	*tmp;

	line = NULL;
	tmp = NULL;
	while (1)
	{
		//signal(SIGINT, &handle_signal_here_doc);
		//signal(SIGQUIT, SIG_IGN);
		tmp = clean_str(limiter);
		line = readline("> ");
		if (g_sig_received == SIGINT)
		{
			g_sig_received = 0;
			close(fd);
			close(main->fd[0]);
			close(main->fd[1]);
			dup2(main->original_stdin, STDIN_FILENO);
			close(main->original_stdin);
			close(main->here_doc_stdin);
			exit(0);
		}
		if (!line)
		{
			ft_putstr_fd("here-document delimited by end-of-file (wanted `", 2);
			ft_putstr_fd(tmp, 2);
			ft_putstr_fd("')\n", 2);
			free(tmp);
			break ;
		}
		else if (ft_strncmp(line, tmp, ft_strlen(limiter)) == 0
			&& (ft_strlen(line)) == ft_strlen(limiter))
		{
			free(tmp);
			break ;
		}
		if ((limiter[0] != '"' && limiter[ft_strlen(limiter) - 1] != '"')
			&& (limiter[0] != '\''
				&& limiter[ft_strlen(limiter) - 1] != '\''))
			line = ft_expand_here_doc(line, main);
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free(line);
		free(tmp);
	}
	return(line);
}

void	here_doc(char *limiter, t_main *main)
{
	int		fd;
	char	*line;

	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, &handle_signal_here_doc);
	main->hpath = rand_path();
	fd = open(main->hpath, O_CREAT | O_TRUNC | O_WRONLY | O_APPEND, 0644);
	dup2(main->here_doc_stdin, STDIN_FILENO);
	line = while_here_doc(main, limiter, fd);
	free(line);
	if (g_sig_received != SIGINT)
		close(STDIN_FILENO);
	free(limiter);
	close(fd);
	ft_got_signal(1);
}
