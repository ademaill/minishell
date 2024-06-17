/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnavarre <vnavarre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 09:05:06 by vnavarre          #+#    #+#             */
/*   Updated: 2024/06/10 16:43:08 by vnavarre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	handle_signal_here_doc(int sgn)
{
	g_sig_received = sgn;
	close(STDIN_FILENO);
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

static char	*while_here_doc(t_main *main, char *limiter, int fd, char *line)
{
	char	*tmp;

	tmp = NULL;
	while (1)
	{
		tmp = clean_str(limiter);
		line = readline("> ");
		core_while(fd, main, tmp, line);
		if (!line)
			break ;
		else if (ft_strncmp(line, tmp, ft_strlen(tmp)) == 0
			&& (ft_strlen(line)) == ft_strlen(tmp))
		{
			free(tmp);
			break ;
		}
		if ((limiter[0] != '"' && limiter[ft_strlen(limiter) - 1] != '"')
			&& (limiter[0] != '\''
				&& limiter[ft_strlen(limiter) - 1] != '\''))
			line = ft_expand_here_doc(line, main);
		end_of_while(fd, line, tmp);
	}
	return (line);
}

void	here_doc(char *limiter, t_main *main)
{
	int		fd;
	char	*line;

	line = NULL;
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, &handle_signal_here_doc);
	main->hpath = rand_path(main);
	fd = open(main->hpath, O_CREAT | O_TRUNC | O_WRONLY | O_APPEND, 0644);
	close(STDIN_FILENO);
	dup2(main->here_doc_stdin, STDIN_FILENO);
	line = while_here_doc(main, limiter, fd, line);
	dup2(main->fd[0], STDIN_FILENO);
	free(line);
	close(fd);
	if (g_sig_received != SIGINT)
		close(STDIN_FILENO);
	ft_got_signal(1);
}
