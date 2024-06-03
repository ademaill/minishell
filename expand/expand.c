/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnavarre <vnavarre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 15:50:46 by vnavarre          #+#    #+#             */
/*   Updated: 2024/06/03 11:42:54 by vnavarre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static bool	ft_is_valid_var_char(char c)
{
	if (ft_isalnum(c) || c == '_')
		return (true);
	return (false);
}

char	*handle_next(int *i, char *tmp, char *str, t_main *main)
{
	size_t	start;
	char	*var;
	char	*env_val;

	start = *i;
	while (ft_is_valid_var_char(str[*i]))
		(*i)++;
	var = ft_substr(str, start, *i - start);
	env_val = ft_get_envlst_val(var, main->env);
	free(var);
	if (!env_val)
	{
		tmp = ft_strdup("");
		return (tmp);
	}
	tmp = ft_strdup(env_val);
	if (str[*i] == '\'')
	{
		tmp[ft_strlen(tmp)] = '\'';
		(*i)++;
	}
	return (tmp);
}

char	*ft_handle_dollars(char *str, int *i, t_main *main)
{
	char	*tmp;

	(*i)++;
	tmp = NULL;
	if (ft_isdigit(str[*i]) || str[*i] == '@')
	{
		if (str[*i + 1] != '\0')
			(*i)++;
		tmp = ft_strdup("");
		return (tmp);
	}
	else if (str[*i] == '?')
	{
		(*i)++;
		tmp = ft_itoa(main->exit_code);
		return (tmp);
	}
	else if (!ft_is_valid_var_char(str[*i]))
	{
		(*i)++;
		tmp = ft_strdup("$");
		return (tmp);
	}
	tmp = handle_next(i, tmp, str, main);
	return (tmp);
}

char	*ft_cmd_pre_expand(char *str, t_main *main)
{
	char	*ret;
	int		i;
	bool	dquotes;

	ret = ft_strdup("");
	i = 0;
	while (str[i])
	{
		if (str[i] == '"' && str[ft_strlen(str) - 1] == '"')
		{
			dquotes = true;
			break ;
		}
		dquotes = false;
		i++;
	}
	i = 0;
	while (str[i])
	{
		if (str[i] == '$')
			ret = ft_strjoin(ret, ft_handle_dollars(str, &i, main));
		else if (str[i] == '"')
			ret = ft_strjoin(ret, ft_handle_d_quotes(str, &i));
		else if (str[i] == '\'')
			ret = ft_strjoin(ret, ft_handle_s_quotes(str, &i, dquotes));
		else
			ret = ft_strjoin(ret, ft_handle_str(str, &i));
	}
	return (ret);
}
