/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnavarre <vnavarre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 09:05:06 by vnavarre          #+#    #+#             */
/*   Updated: 2024/06/05 14:28:45 by vnavarre         ###   ########.fr       */
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
			ret = ft_strjoin(ret, ft_handle_d_quotes(str, &i, true));
		else if (str[i] == '\'')
			ret = ft_strjoin(ret, ft_handle_s_quotes(str, &i, true));
		else
			ret = ft_strjoin(ret, ft_handle_str(str, &i));
	}
	return (ret);
}

/*static char	*clean_limiter(char *limiter)
{
	int		i;
	char	*str;
	int		j;

	i = 0;
	j = 0;
	str = ft_calloc(sizeof(char), ft_strlen(limiter) + 1);
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
}*/

void	here_doc(char *limiter, t_main *main)
{
	int		fd;
	char	*line;

	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, &handle_signal_here_doc);
	main->heredoc_path = rand_path();
	fd = open(main->heredoc_path, O_CREAT | O_TRUNC | O_WRONLY | O_APPEND, 0644);
	dup2(main->here_doc_stdin, STDIN_FILENO);
	while (1)
	{
		signal(SIGINT, &handle_signal_here_doc);
		signal(SIGQUIT, SIG_IGN);
		line = readline("> ");
		if (!line)
		{
			ft_putstr_fd("bash: warning: ", 2);
			ft_putstr_fd("here-document delimited by end-of-file (wanted `", 2);
			ft_putstr_fd(clean_str(limiter), 2);
			ft_putstr_fd("')\n", 2);
			break;
		}
		if (ft_strncmp(line, clean_str(limiter), ft_strlen(limiter)) == 0 && (ft_strlen(line)) == ft_strlen(limiter))
			break ;
		if ((limiter[0] != '"' && limiter[ft_strlen(limiter) - 1] != '"') && (limiter[0] != '\'' && limiter[ft_strlen(limiter) - 1] != '\''))
			line = ft_expand_here_doc(line, main);
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free(line);
	}
	free(line);
	close(fd);
}
