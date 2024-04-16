/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnavarre <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 15:26:38 by vnavarre          #+#    #+#             */
/*   Updated: 2023/11/17 12:59:11 by vnavarre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_words(char const *str, char c)
{
	size_t	i;
	size_t	count;

	i = 0;
	count = 0;
	if (str[0] == '\0')
		return (0);
	if (str[i] != c)
		count++;
	while (str[i] != '\0')
	{
		if (str[i] == c && (str[i + 1] != c && str[i + 1] != '\0'))
			count++;
		i++;
	}
	return (count);
}

static void	incr_var(int *m, int *i)
{
	*m = *m + 1;
	*i = *i + 1;
}

char	**ft_split(char const *s, char c)
{
	int		i;
	int		m;
	int		t;
	char	**arr;

	if (s == NULL)
		return (NULL);
	arr = ft_calloc(sizeof(char *), (count_words(s, c) + 1));
	i = 0;
	t = 0;
	if (!arr)
		return (NULL);
	while (t < count_words(s, c) && s[i])
	{
		m = 0;
		while (s[i] == c)
			i++;
		while (s[i] != c && s[i] != '\0')
			incr_var(&m, &i);
		arr[t] = ft_substr(s, i - m, m);
		if (!arr[t])
			return (NULL);
		t++;
	}
	return (arr);
}
