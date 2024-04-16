/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnavarre <vnavarre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 13:35:32 by vnavarre          #+#    #+#             */
/*   Updated: 2024/03/21 13:38:34 by vnavarre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_pwd(void)
{
	char *dir;

	dir = NULL;
	dir = getcwd(dir, 0);
	if (!dir)
		return (0);
	printf("%s\n", dir);
	return (1);
}

int	main(void)
{
	ft_pwd();
	return (0);
}
