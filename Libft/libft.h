/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnavarre <vnavarre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 10:19:24 by vnavarre          #+#    #+#             */
/*   Updated: 2024/06/17 14:14:52 by vnavarre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdlib.h>
# include <unistd.h>
# include <stdbool.h>
# include <stdint.h>
# include <limits.h>
# include "../minishell.h"

typedef struct s_token	t_token;
typedef struct s_env	t_env;
typedef struct s_main	t_main;

int		ft_isalpha(int a);
int		ft_isdigit(int a);
int		ft_isalnum(int a);
int		ft_isascii(int a);
int		ft_isprint(int a);
size_t	ft_strlen(const char *str);
void	*ft_memset(void *s, int c, size_t n);
void	ft_bzero(void *s, size_t n);
void	*ft_memcpy(void *dest, const void *src, size_t n);
void	*ft_memmove(void *dest, const void *src, size_t n);
size_t	ft_strlcpy(char *dest, const char *src, size_t size);
size_t	ft_strlcat(char *dst, const char *src, size_t size);
int		ft_toupper(int c);
int		ft_tolower(int c);
char	*ft_strchr(const char *s, int c);
char	*ft_strrchr(const char *s, int c);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
void	*ft_memchr(const void *s, int c, size_t n);
int		ft_memcmp(const void *s1, const void *s2, size_t n);
char	*ft_strnstr(const char *big, const char *little, size_t len);
int		ft_atoi(const char *nptr);
void	*ft_calloc(size_t nmemb, size_t size);
char	*ft_strdup(const char *s);
char	*ft_substr(char const *s, unsigned int strat, size_t len);
char	*ft_strjoin(char *s1, char *s2, bool mal);
char	*ft_strtrim(char const *s1, char const *set);
char	**ft_split(char const *s, char c);
char	*ft_itoa(int n);
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));
void	ft_striteri(char *s, void (*f)(unsigned int, char*));
void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);
void	ft_putendl_fd(char *s, int fd);
void	ft_putnbr_fd(int n, int fd);
void	ft_lstadd_front(t_token **lst, t_token *new);
int		ft_lstsize(t_env *lst);
t_token	*ft_lstlast(t_token *lst);
void	ft_lstadd_back(t_token **lst, t_token *new);
void	ft_lstdelone(t_token *lst, void (*del)(void*));
void	ft_lstclear(t_token **lst, void (*del)(void*));
void	ft_lstiter(t_token *lst, void (*f)(void *));
t_token	*ft_lstmap(t_token *lst, void *(*f)(void *), void (*del)(void *));
int		ft_size(char *line, int *i);
void	ft_skip_space(char *line, int *i);
void	ft_ignore_sep(char *line, int *i);
char	*ft_strndup(const char *str, int j);
void	ft_new_node(t_token **lst, char	**content);
t_token	*ft_lstnew(char **content);
t_token	*ft_lstfirst(t_token *lst);
void	ft_free_token(t_token *token);
int		ft_len_tab(char **tab);

#endif
