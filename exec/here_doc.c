/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademaill <ademaill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 09:05:06 by vnavarre          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2024/04/17 13:56:58 by ademaill         ###   ########.fr       */
=======
/*   Updated: 2024/04/17 15:18:10 by vnavarre         ###   ########.fr       */
>>>>>>> ccf0314b711a31f9f62f1f0cf593f3dedfa369e8
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

<<<<<<< HEAD
static void	free_rest_gnl(int fd, char *line, char *limiter)
=======
static void    free_rest_gnl(int fd, char *line)
>>>>>>> ccf0314b711a31f9f62f1f0cf593f3dedfa369e8
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

	path = rand_path();
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
