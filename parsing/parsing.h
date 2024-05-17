/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnavarre <vnavarre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 10:33:29 by ademaill          #+#    #+#             */
/*   Updated: 2024/05/17 12:21:02 by vnavarre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "../minishell.h"
# include <stdbool.h>

typedef struct s_main	t_main;

void	parse_pipe(t_token *token, t_main *main);
void	parse_here_doc(t_token *token, t_main *main);
void	parse_redirect(t_token *token, t_main *main);
void	parse_append(t_token *token, t_main *main);
void	parse_redirect(t_token *token, t_main *main);
void	error_parse(char *str, t_token *token, t_main *main);
void	str_modify(t_token *token);
void	str_modify2(t_token *token);

#endif
