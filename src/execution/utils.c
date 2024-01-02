/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maroy <maroy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 20:15:19 by maroy             #+#    #+#             */
/*   Updated: 2024/01/02 00:15:54 by maroy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_env_var_by_key(char *key)
{
	int		index;
	char	*value;

	value = NULL;
	index = 0;
	if (!key)
		return (NULL);
	index = find_env_var_index(key, g_global->env_var);
	if (index == -1)
		return (NULL);
	value = return_value(g_global->env_var[index], '=');
	return (value);
}

static int	check_only_key(char *key)
{
	int	i;

	i = -1;
	if (!key)
		return (-1);
	while (g_global->env_var[++i])
	{
		if (!ft_strequal(g_global->env_var[i], key))
			return (i);
	}
	return (-1);
}

int	find_env_var_index(char *key, char **env_pointer)
{
	int		index;
	char	*sub_env;
	int		i;

	i = -1;
	if (!key)
		return (-1);
	while (env_pointer[++i])
	{
		index = get_str_from_char(env_pointer[i], '=', FALSE);
		if (index == -1)
			index = ft_strlen(env_pointer[i]);
		else
		{
			sub_env = ft_substr(env_pointer[i], 0, index);
			if (sub_env != NULL && ft_strequal(key, sub_env))
			{
				ft_free(sub_env);
				return (i);
			}
			ft_free(sub_env);
		}
	}
	return (check_only_key(key));
}
