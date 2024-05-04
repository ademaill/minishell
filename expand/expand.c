/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnavarre <vnavarre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 15:50:46 by vnavarre          #+#    #+#             */
/*   Updated: 2024/05/02 14:12:33 by vnavarre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static bool	ft_is_valid_var_char(char c)
{
	if (ft_isalnum(c) || c == '_')
		return (true);
	return (false);
}

static char	*ft_handle_dollars(char *str, int *i, t_env *env)
{
	size_t	start;
	char	*var;
	char	*tmp;
	char	*env_val;

	(*i)++;
	if (ft_isdigit(str[*i]) || str[*i] == '@')
	{
		(*i)++;
		tmp = ft_strdup("");
		return (tmp);
	}
	/*else if (str[*i] == '?')
	{
		(*i)++;
		return(ft_itoa(main->exit_code));
	}*/
	else if (!ft_is_valid_var_char(str[*i]))
	{
		str = ft_strdup("$");
		return (str);
	}
	start = *i;
	while (ft_is_valid_var_char(str[*i]))
		(*i)++;
	var = ft_substr(str, start, *i - start);
	env_val = ft_get_envlst_val(var, env);
	free(var);
	if (!env_val)
	{
		tmp = ft_strdup("");
		return (tmp);
	}
	tmp = ft_strdup(env_val);
	if (str[*i] == '\'')
	{
		tmp[ft_strlen(tmp) - 1] = '\'';
		(*i)++;
	}
	return (tmp);
}

char	*ft_cmd_pre_expand(char *str, t_env *env)
{
	char	*ret;
	int		i;

	ret = ft_strdup("");
	i = 0;
	while (str[i])
	{
		if (str[i] == '$')
			ret = ft_strjoin(ret, ft_handle_dollars(str, &i, env));
		else if (str[i] == '"')
			ret = ft_strjoin(ret, ft_handle_d_quotes(str, &i));
		else if (str[i] == '\'')
			ret = ft_strjoin(ret, ft_handle_s_quotes(str, &i));
		else
			ret = ft_strjoin(ret, ft_handle_str(str, &i));
	}
	return (ret);
}
