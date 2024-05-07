/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnavarre <vnavarre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 09:05:06 by vnavarre          #+#    #+#             */
/*   Updated: 2024/05/07 15:32:23 by vnavarre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void    free_rest_gnl(int fd, char *line)
{
	free(line);
	close(fd);
	line = get_next_line(fd);
	free(line);
}

char	*here_doc(char *limiter)
{
	int		fd;
	char	*line;
	char	*path;

	path = rand_spath();
	fd = open(path, O_CREAT | O_TRUNC | O_WRONLY | O_APPEND, 0644);
	write(STDOUT_FILENO, ">", 1);
	line = get_next_line(STDIN_FILENO);
	while (ft_strncmp(line, limiter, ft_strlen(limiter)) != 0)
	{
		write(STDOUT_FILENO, ">", 1);
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
