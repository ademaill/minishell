/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademaill <ademaill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 15:38:51 by ademaill          #+#    #+#             */
/*   Updated: 2024/04/17 10:20:00 by ademaill         ###   ########.fr       */
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
int		ft_size(char *line, int *i);
char	**ft_split_ms(char *s, char *sep);
char	*ft_substr(char const *s, unsigned int start, size_t len);
//void	*ft_calloc(size_t nmemb, size_t size);
//void	ft_bzero(void *s, size_t n);
//size_t	ft_strlen(const char *s);
//int		ft_strchr(const char *s, int c);
char	*ft_strndup(const char *str, int j);
//t_token	*ft_lstnew(char **content);
//void	ft_lstadd_back(t_token **lst, t_token *new);
int		ft_isnum(char c);

#endif
