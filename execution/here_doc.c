/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademaill <ademaill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 09:05:06 by vnavarre          #+#    #+#             */
/*   Updated: 2024/06/03 17:44:25 by ademaill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	handle_signal_here_doc(int sgn)
{
	g_sig_received = sgn;
	exit(1);
}

static void	free_rest_gnl(int fd, char *line)
{
	free(line);
	close(fd);
	line = readline("> ");
	free(line);
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
			ret = ft_strjoin(ret, ft_handle_dollars(str, &i, main));
		else if (str[i] == '"')
			ret = ft_strjoin(ret, ft_handle_d_quotes(str, &i));
		else if (str[i] == '\'')
			ret = ft_strjoin(ret, ft_handle_s_quotes(str, &i, true));
		else
			ret = ft_strjoin(ret, ft_handle_str(str, &i));
	}
	return (ret);
}

static void	while_here_doc(char *line, char *limiter, char *tmp, t_main *main, int fd)
{
	while (ft_strncmp(line, limiter, ft_strlen(limiter)) != 0
		|| (ft_strlen(line) - 1) == ft_strlen(limiter))
	{
		signal(SIGQUIT, SIG_IGN);
		if ((tmp[0] != '"' && tmp[ft_strlen(tmp) - 1] != '"')
			&& (tmp[0] != '\'' && tmp[ft_strlen(tmp) - 1] != '\''))
			line = ft_expand_here_doc(line, main);
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free(line);
		line = readline("> ");
		if (!line)
			break ;
	}
}

char	*here_doc(char *limiter, t_main *main)
{
	int		fd;
	char	*line;
	char	*path;
	char	*tmp;

	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, &handle_signal_here_doc);
	path = rand_path();
	tmp = limiter;
	limiter = clean_limiter(limiter);
	fd = open(path, O_CREAT | O_TRUNC | O_WRONLY | O_APPEND, 0644);
	line = readline("> ");
	while_here_doc(line, limiter, tmp, main, fd);
	free_rest_gnl(fd, line);
	return (path);
}
