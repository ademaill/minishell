/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademaill <ademaill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 15:56:23 by ademaill          #+#    #+#             */
/*   Updated: 2024/04/11 16:05:38 by ademaill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lexer.h"

static	int	ft_count_words(const char *str, const char sep)
{
	int	i;
	int	w;

	i = 0;
	w = 0;
	if (str[0] == '\0')
		return (0);
	if (str[0] != sep)
		w++;
	while (str[i] != '\0')
	{
		if (str[i] == sep && (str[i + 1] != sep && str[i + 1] != '\0'))
			w++;
		i++;
	}
	return (w);
}

static	void	ft_init(int *t, int *i)
{
	*t = -1;
	*i = 0;
}

static	void	ft_incr(int *i, int *m)
{
	*i = *i + 1;
	*m = *m + 1;
}

char	**ft_split(char const *s, char c)
{
	int		i;
	int			t;
	int			m;
	char		**arr;

	ft_init(&t, &i);
	if (!s)
		return (NULL);
	arr = (char **)ft_calloc(sizeof(char *), (ft_count_words(s, c) + 1));
	if (!arr)
		return (NULL);
	ft_skip_space((char *)s, &i);
	while (++t < ft_count_words(s, c) && s[i])
	{
		m = 0;
		while (s[i] == c)
			i++;
		while (s[i] != c && s[i] != '\0')
			ft_incr(&i, &m);
		arr[t] = ft_substr(s, (i - m), m);
		if (!arr[t])
			return (NULL);
	}
	return (arr);
}
