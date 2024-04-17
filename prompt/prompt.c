/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnavarre <vnavarre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 12:06:28 by ademaill          #+#    #+#             */
/*   Updated: 2024/04/17 10:48:30 by vnavarre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>
#include <unistd.h>
#include "../minishell.h"

static char	*ft_get_prompt(void)
{
	char	*tmp_pwd;
	char	*prompt;

	tmp_pwd = NULL;
	prompt = NULL;
	tmp_pwd = getcwd(tmp_pwd, 0);
	if (!tmp_pwd)
		return (NULL);
	prompt = ft_strjoin("Minishell-ademaill-vnavarre", tmp_pwd);
	return (prompt);
}

int	main(void)
{
	char	*buffer;
	char	*prompt;
	t_token	*arr;
	int	i;

	i = 0;
	while (1)
	{
		prompt = ft_get_prompt();
		buffer = readline(prompt);
		if (buffer == NULL)
			break;
		arr = ft_tokenizer(buffer);
		while (arr)
		{
			printf("token numero %d\n", i);
			i++;
			printf("%s\n", arr->value[0]);
			if (arr->value[1])
				printf("%s\n", arr->value[1]);
			if (arr->type == 0)
				printf("type : _cmdgrp\n\n");
			else if (arr->type == 1)
				printf("type : _pipe\n\n");
			else if (arr->type == 2)
				printf("type : _redirect\n\n");
			else if (arr->type == 3)
				printf("type : _var_env\n\n");
			else if (arr->type == 4)
				printf("type : _here_doc\n\n");
			else if (arr->type == 5)
				printf("type : _append\n\n");
			arr = arr->next;
		}
	}
	printf("Bye \n");
	free(buffer);
	while (arr)
	{
		printf("token numero %d\n", i);
		i++;
		printf("%s\n", arr->value[0]);
		if (arr->value[1])
			printf("%s\n", arr->value[1]);
		if (arr->type == 0)
			printf("type : _cmdgrp\n\n");
		else if (arr->type == 1)
			printf("type : _pipe\n\n");
		else if (arr->type == 2)
			printf("type : _redirect\n\n");
		else if (arr->type == 3)
			printf("type : _var_env\n\n");
		else if (arr->type == 4)
			printf("type : _here_doc\n\n");
		else if (arr->type == 5)
			printf("type : _append\n\n");
		arr = arr->next;
	}
	return (0);
}
