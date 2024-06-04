/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademaill <ademaill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 09:58:48 by ademaill          #+#    #+#             */
/*   Updated: 2024/06/04 10:35:36 by ademaill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	parse_pipe(t_token *token, t_main *main)
{
	if ((token->next && (token->next->value[0][0] == '|'))
		|| token->value[0][1] == '|')
		error_parse("Pipe cannot be followed by a second pipe\n", token, main);
	else if (token->prev && (token->prev->value[0][0] == '|'))
		error_parse("Pipe cannot be preceded by a second pipe\n", token, main);
	else if (!token->prev)
		error_parse("near unexpected token '|'\n", token, main);
	else
		token->type = __pipe;
}

void	parse_here_doc(t_token *token, t_main *main)
{
	if (token->value[1] && (token->value[1][0] == '|'))
		error_parse("Here_doc cannot be followed by a pipe\n", token, main);
	else if (token->value[0][2] && (token->value[0][2] == '<'))
		error_parse("To mutch <\n", token, main);
	else if (token->value[0][2] && (token->value[0][2] == '>'))
		error_parse("Here doc cannot be followed by >\n", token, main);
	else if (token->value[1] && (token->value[1][0] == '<'))
		error_parse("To mutch <\n", token, main);
	else if (token->value[1] && (token->value[1][0] == '>'))
		error_parse("Here doc cannot be followed by >\n", token, main);
	if (token->value[0][0] == '<' && token->value[0][1] == '<')
	{
		if (token->value[0][2] != '\0')
			str_modify2(token);
		if (token->value[1] && token->value[1][0] == '|')
			error_parse("Here_doc can't be followed by a pipe\n", token, main);
	}
	if (token->value[0][0] == '<' && token->value[0][1] == '<'
		&& !token->value[1])
		error_parse("Missing limiter for here doc\n", token, main);
	token->type = __here_doc;
}

static void	ft_parse_out(t_token *token, t_main *main)
{
	if (token->value[0][1] != '\0')
		str_modify(token);
	if (token->value[1] && token->value[1][0] == '|')
		error_parse("Redirect can't be followed by a pipe\n", token, main);
	if (token->value[1] &&
		(token->value[1][0] == '<' || token->value[1][0] == '>'))
		error_parse(" syntax error near unexpected token\n", token, main);
	if (!token->value[1])
		error_parse("Redirect need file\n", token, main);
	if (!open(token->value[1], O_RDONLY))
		error_parse("File doesn't exist\n", token, main);
	token->type = __redirect_out;
}

void	parse_redirect(t_token *token, t_main *main)
{
	if (token->value[0][0] == '<')
	{
		if (token->value[0][1] != '\0')
			str_modify(token);
		if (token->value[1] && token->value[1][0] == '|')
			error_parse("Redirect can't be followed by a pipe\n", token, main);
		if (token->value[1] &&
			(token->value[1][0] == '<' || token->value[1][0] == '>'))
			error_parse("Syntax error near unexpected token\n", token, main);
		if (!token->value[1])
			error_parse("Redirect need file\n", token, main);
		if (!open(token->value[1], O_RDONLY))
			error_parse("File doesn't exist\n", token, main);
		token->type = __redirect_in;
	}
	if (token->value[0][0] == '>')
		ft_parse_out(token, main);
}

void	parse_append(t_token *token, t_main *main)
{
	if (token->value[0][2] && token->value[0][2] == '<')
		error_parse("Append cannot be followed by <\n", token, main);
	if (token->value[0][2] && token->value[0][2] == '>')
		error_parse("Append cannot be followed by >\n", token, main);
	if (token->value[1] && token->value[1][0] == '>')
		error_parse("Append cannot be followed by >\n", token, main);
	if (token->value[1] && token->value[1][0] == '<')
		error_parse("Append cannot be followed by <\n", token, main);
	if (token->value[0][0] == '>' && token->value[0][1] == '>')
	{
		if (token->value[0][2] != '\0')
			str_modify2(token);
		if (token->value[1] && token->value[1][0] == '|')
			error_parse("Append cannot be followed by a pipe\n", token, main);
	}
	if (token->value[0][0] == '>' && token->value[0][1] == '>'
		&& !token->value[1])
		error_parse("Missing file for append\n", token, main);
	token->type = __append;
}
