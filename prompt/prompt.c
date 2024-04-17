/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademaill <ademaill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 12:06:28 by ademaill          #+#    #+#             */
/*   Updated: 2024/04/17 13:28:40 by ademaill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <unistd.h>
#include "../minishell.h"


static char	*ft_get_prompt(void)
{
	char	*tmp_pwd;
	char	*prompt;

	tmp_pwd = NULL;
	prompt = NULL;
	tmp_pwd = getcwd(tmp_pwd, 0);
	tmp_pwd = ft_strjoin(tmp_pwd, "$ ");
	if (!tmp_pwd)
		return (NULL);
	prompt = ft_strjoin("Minishell-ademaill-vnavarre", tmp_pwd);
	free(tmp_pwd);
	return (prompt);
}

int	main(void)
{
	char	*buffer;
	char	*prompt;
	t_token	*arr;
	int	i;
	t_token	*tmp;

	i = 0;
	while (1)
	{
		prompt = ft_get_prompt();
		buffer = readline(prompt);
		free(prompt);
		if (buffer == NULL)
		{
			printf("Bye \n");
			return (0);
		}
		arr = ft_tokenizer(buffer);
		tmp = arr;
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
	t_token *lst;
	lst = tmp;
	while (lst)
	{
		tmp = lst->next;
		i = 0;
		while (lst->value[i])
		{
			free(lst->value[i]);
			i++;
		}
		free(lst->value);
		free(lst);
		lst = tmp;
	}
	free(lst);
	printf("Bye \n");
	free(buffer);
}
