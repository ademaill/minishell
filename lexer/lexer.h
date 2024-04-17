/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademaill <ademaill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 15:38:51 by ademaill          #+#    #+#             */
/*   Updated: 2024/04/17 12:12:52 by ademaill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include <stdlib.h>
# include <unistd.h>
#include "../minishell.h"

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

t_token	*ft_tokenizer(char *line);


#endif
