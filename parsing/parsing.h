/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademaill <ademaill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 10:33:29 by ademaill          #+#    #+#             */
/*   Updated: 2024/04/18 16:39:38 by ademaill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

#include "../minishell.h"

void	parse_pipe(t_token *token);
void	parse_here_doc(t_token *token);
void	parse_redirect(t_token *token);
void	parse_append(t_token *token);
void	parse_redirect(t_token *token);
void	error_parse(char *str, t_token *token);
void	str_modify(t_token *token);
void	str_modify2(t_token *token);

#endif
