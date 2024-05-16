/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnavarre <vnavarre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 09:05:06 by vnavarre          #+#    #+#             */
/*   Updated: 2024/05/16 12:58:10 by vnavarre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	free_rest_gnl(int fd, char *line)
{
	free(line);
	close(fd);
	line = get_next_line(fd);
	free(line);
}

static char	*ft_expand_here_doc(char *str, t_main *main)
{
	char	*ret;
	int		i;

	i = 0;
	ret = ft_strdup("");
	while (str[i])
	{
		if (str[i] == '$')
			ret = ft_strjoin(ret, ft_handle_dollars(str, &i, main));
		else
			ret = ft_strjoin(ret, ft_handle_str(str, &i));
	}
	return (ret);
}

char	*here_doc(char *limiter, t_main *main)
{
	int		fd;
	char	*line;
	char	*path;

	path = rand_path();
	fd = open(path, O_CREAT | O_TRUNC | O_WRONLY | O_APPEND, 0644);
	write(STDOUT_FILENO, ">", 1);
	line = get_next_line(STDIN_FILENO);
	while (ft_strncmp(line, limiter, ft_strlen(limiter)) != 0)
	{
		write(STDOUT_FILENO, ">", 1);
		line = ft_expand_here_doc(line, main);
		write(fd, line, ft_strlen(line));
		free(line);
		line = get_next_line(STDIN_FILENO);
		if (!line)
			break ;
	}
	free_rest_gnl(fd, line);
	close(fd);
	return (path);
}
