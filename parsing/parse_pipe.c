/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnavarre <vnavarre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 09:58:48 by ademaill          #+#    #+#             */
/*   Updated: 2024/06/08 11:38:04 by vnavarre         ###   ########.fr       */
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
		error_parse("Near unexpected token '|'\n", token, main);
	else if (!token->next)
		error_parse("Near unexpected token '|'\n", token, main);
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
			error_parse("Here_doc cannot be followed by a pipe\n", token, main);
	}
	if (!token->value[1])
		error_parse("Here_doc need limiter\n", token, main);
	token->type = __here_doc;
}

static void	parse_out(t_token *token, t_main *main)
{
	if (token->value[0][1] != '\0')
		str_modify(token);
	if (token->value[1] && token->value[1][0] == '|')
		error_parse("Redirect cannot be followed by a pipe\n", token, main);
	if (token->value[1] && (token->value[1][0] == '<'
		|| token->value[1][0] == '>'))
		error_parse(" syntax error near unexpected token\n", token, main);
	if (!token->value[1])
		error_parse("Redirect need file\n", token, main);
	token->type = __redirect_out;
}

void	parse_redirect(t_token *token, t_main *main)
{
	char	*tmp;

	tmp = NULL;
	if (token->value[1])
		tmp = clean_str(token->value[1]);
	if (token->value[0][0] == '<')
	{
		if (token->value[0][1] != '\0')
			str_modify(token);
		if (token->value[1] && token->value[1][0] == '|')
			error_parse("Redirect cannot be followed by a pipe\n", token, main);
		if (token->value[1] && (token->value[1][0] == '<'
			|| token->value[1][0] == '>'))
			error_parse(" syntax error near unexpected token\n", token, main);
		if (!token->value[1])
			error_parse("Redirect need file\n", token, main);
		token->type = __redirect_in;
	}
	free(tmp);
	if (token->value[0][0] == '>')
		parse_out(token, main);
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
	if (!token->value[1])
		error_parse("Append need file\n", token, main);
	token->type = __append;
}
