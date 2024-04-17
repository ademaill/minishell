/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnavarre <vnavarre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 16:24:59 by vnavarre          #+#    #+#             */
/*   Updated: 2024/04/12 11:56:53 by vnavarre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (!s1 || !s2)
		return (-1);
	while ((s1[i] == s2[i] && i < n) && s1[i] != '\0')
		i++;
	if (i == n)
		return (0);
	if (ft_isascii(s1[i]) == 0)
		return (s2[i] - s1[i]);
	return (s1[i] - s2[i]);
}
