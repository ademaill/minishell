/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnavarre <vnavarre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 15:38:51 by ademaill          #+#    #+#             */
/*   Updated: 2024/05/02 12:58:05 by vnavarre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

typedef enum e_type
{
	__cmdgr,
	__pipe,
	__redirect,
	__var_env,
	__here_doc,
	__append,

}	t_type;

typedef struct s_token
{
	t_type type;
	char	**value;
	struct s_token *prev;
	struct s_token *next;
}	t_token;


#endif
