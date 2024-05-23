/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnavarre <vnavarre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 13:35:32 by vnavarre          #+#    #+#             */
/*   Updated: 2024/05/21 13:44:47 by vnavarre         ###   ########.fr       */
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
	return (0);
}
