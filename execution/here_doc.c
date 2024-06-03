/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademaill <ademaill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 09:05:06 by vnavarre          #+#    #+#             */
/*   Updated: 2024/06/03 14:53:02 by ademaill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	handle_signal_here_doc(int sgn)
{
	g_sig_received = sgn;
	exit(1);
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

static void	free_rest_gnl(int fd, char *line)
{
	free(line);
	close(fd);
	line = get_next_line(fd);
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

static char	*clean_limiter(char *limiter)
{
	int		i;
	char	*str;
	int		j;

	i = 0;
	j = 0;
	str = malloc(sizeof(char) * ft_strlen(limiter) - 1);
	if (!str)
		return (NULL);
	if (limiter[i] == '"')
		i++;
	while (limiter[i] && limiter[i] != '"')
	{
		str[j] = limiter[i];
		i++;
		j++;
	}
	str[j] = '\0';
	return (str);
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
	if (!line)
	{
		printf ("\n");
		return (path);
	}
	while (ft_strncmp(line, limiter, ft_strlen(limiter)) != 0)
	{
		signal(SIGQUIT, SIG_IGN);
		if ((tmp[0] != '"' && tmp[ft_strlen(tmp) - 1] != '"') && (tmp[0] != '\'' && tmp[ft_strlen(tmp) - 1] != '\''))
			line = ft_expand_here_doc(line, main);
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free(line);
		line = readline("> ");
		if (!line)
			break ;
	}
	free_rest_gnl(fd, line);
	close(fd);
	return (path);
}
