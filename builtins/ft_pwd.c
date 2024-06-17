/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnavarre <vnavarre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 13:35:32 by vnavarre          #+#    #+#             */
/*   Updated: 2024/06/07 19:41:41 by vnavarre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_pwd(void)
{
	char	*dir;

	dir = NULL;
	dir = getcwd(dir, 0);
	if (!dir)
		return (1);
	printf("%s\n", dir);
	free(dir);
	return (0);
}
