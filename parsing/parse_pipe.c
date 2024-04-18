/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademaill <ademaill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 09:58:48 by ademaill          #+#    #+#             */
/*   Updated: 2024/04/18 13:14:41 by ademaill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	parse_pipe(t_token *token)
{
	if (token->next && (token->next->value[0][0] == '|'))
		error_parse("one pipe cannot be followed by a second pipe");
	else if (token->prev && (token->prev->value[0][0] == '|'))
		error_parse("one pipe cannot be preceded by a second pipe");
	else
		token->type == __pipe;
}

void	parse_here_doc(t_token *token)
{
	if (token->next && (token->next->value[0][0] == '|'))
		error_parse("here_doc cannot be followed by a pipe");
	else if (token->value[0][2] && (token->value[0][2] == '<'))
		error_parse("to mutch <");
	else if (token->value[0][2] && (token->value[0][2] == '>'))
		error_parse("here doc cannot be followed by >");
}

void	parse_redirect(t_token *token)
{
	if (token->value[0][0] == '<')
		if (token->value[0][1] != '\0')
			str_modify(token);
		if (!open(token->value[1], O_RDONLY))
			error_parse("file doesn't exist");
	if (token->value[])
}
