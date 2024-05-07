/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnavarre <vnavarre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 15:38:51 by ademaill          #+#    #+#             */
/*   Updated: 2024/05/07 15:31:41 by vnavarre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

typedef enum e_type
{
	__redirect_in,
	__cmdgr,
	__pipe,
	__redirect_out,
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
