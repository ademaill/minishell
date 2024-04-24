/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademaill <ademaill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 09:58:48 by ademaill          #+#    #+#             */
/*   Updated: 2024/04/22 14:36:16 by ademaill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	parse_pipe(t_token *token)
{
	if ((token->next && (token->next->value[0][0] == '|'))
		|| token->value[0][1] == '|')
		error_parse("Pipe cannot be followed by a second pipe\n", token);
	else if (token->prev && (token->prev->value[0][0] == '|'))
		error_parse("Pipe cannot be preceded by a second pipe\n", token);
	else if (!token->prev)
		error_parse("near unexpected token '|'\n", token);
	else
		token->type = __pipe;
}

void	parse_here_doc(t_token *token)
{
	if (token->value[1] && (token->value[1][0] == '|'))
		error_parse("Here_doc cannot be followed by a pipe\n", token);
	else if (token->value[0][2] && (token->value[0][2] == '<'))
		error_parse("To mutch <\n", token);
	else if (token->value[0][2] && (token->value[0][2] == '>'))
		error_parse("Here doc cannot be followed by >\n", token);
	else if (token->value[1] && (token->value[1][0] == '<'))
		error_parse("To mutch <\n", token);
	else if (token->value[1] && (token->value[1][0] == '>'))
		error_parse("Here doc cannot be followed by >\n", token);
	if (token->value[0][0] == '<' && token->value[0][1] == '<')
	{
		if (token->value[0][2] != '\0')
			str_modify2(token);
		if (token->value[1] && token->value[1][0] == '|')
			error_parse("Here_doc cannot be followed by a pipe\n", token);
	}
	token->type = __here_doc;
}

void	parse_redirect(t_token *token)
{
	if (token->next && (token->next->value[0][0] == '|'))
		error_parse("Redirect cannot be followed by a pipe\n", token);
	if (token->value[0][0] == '<')
	{
		if (token->value[0][1] != '\0')
			str_modify(token);
		if (token->value[1][0] == '|')
			error_parse("Redirect cannot be followed by a pipe\n", token);
		if (!open(token->value[1], O_RDONLY))
			error_parse("File doesn't exist\n", token);
	}
	if (token->value[0][0] == '>')
	{
		if (token->value[0][1] != '\0')
			str_modify(token);
		if (token->value[1][0] == '|')
			error_parse("Redirect cannot be followed by a pipe\n", token);
	}
	token->type = __redirect;
}

void	parse_append(t_token *token)
{
	if (token->value[0][2] && token->value[0][2] == '<')
		error_parse("Append cannot be followed by <\n", token);
	if (token->value[0][2] && token->value[0][2] == '>')
		error_parse("Append cannot be followed by >\n", token);
	if (token->value[1] && token->value[1][0] == '>')
		error_parse("Append cannot be followed by >\n", token);
	if (token->value[1] && token->value[1][0] == '<')
		error_parse("Append cannot be followed by <\n", token);
	if (token->value[0][0] == '>' && token->value[0][1] == '>')
	{
		if (token->value[0][2] != '\0')
			str_modify2(token);
		if (token->value[1] && token->value[1][0] == '|')
			error_parse("Append cannot be followed by a pipe\n", token);
	}
	token->type = __append;
}
