/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademaill <ademaill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 13:43:20 by vnavarre          #+#    #+#             */
/*   Updated: 2024/06/17 12:56:25 by ademaill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static char	*generate_rand_str(void)
{
	int			size;
	const char	*fixed_sequence = "ABCDEFGHIJKLMNO";
	char		*str;
	int			i;

	i = 0;
	size = 15;
	str = ft_calloc((size + 1), sizeof(char));
	if (str == NULL)
	{
		ft_putstr_fd("Error\n", 2);
		exit(EXIT_FAILURE);
	}
	while (i < size)
	{
		str[i] = fixed_sequence[i & (i - 1)];
		i++;
	}
	str[size] = '\0';
	return (str);
}

char	*rand_path(t_main *main)
{
	char	*buff;
	char	*path;

	path = NULL;
	buff = NULL;
	buff = generate_rand_str();
	path = ft_strjoin("/tmp/minish_here_doc_", buff, false);
	free(buff);
	if (path == NULL)
		ft_error(path, EXIT_FAILURE, " No such file or directory\n", main);
	return (path);
}

void	core_while(int fd, t_main *main, char *tmp, char *line)
{
	if (g_sig_received == SIGINT)
	{
		g_sig_received = 0;
		close_all(main);
		dup2(main->original_stdin, STDIN_FILENO);
		free(main->hpath);
		free_all(main);
		free(line);
		close(fd);
		free(tmp);
		exit(0);
	}
	if (!line)
	{
		ft_putstr_fd("here-document delimited by end-of-file (wanted `", 2);
		ft_putstr_fd(tmp, 2);
		ft_putstr_fd("')\n", 2);
		free(tmp);
	}
}

void	end_of_while(int fd, char *line, char *tmp)
{
	write(fd, line, ft_strlen(line));
	write(fd, "\n", 1);
	free(line);
	free(tmp);
}
