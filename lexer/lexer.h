/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademaill <ademaill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 15:38:51 by ademaill          #+#    #+#             */
/*   Updated: 2024/05/24 15:04:49 by ademaill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H
#include <stdbool.h>
#include "../minishell.h"

typedef struct s_main	t_main;

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
	t_type			type;
	char			**value;
	struct s_token	*prev;
	struct s_token	*next;
}	t_token;

int		regroup(t_token *token, t_token	*tmp, t_token *tmp2, t_token *tmp3);
void	free_tab(char **tab);
int		ft_token_join(t_token *src, t_token *add, int j);
char	**ft_split_ms(char *str, char *sep);
void	clear_token(t_main *main);

#endif
