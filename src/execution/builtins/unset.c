/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maroy <maroy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 14:05:13 by maroy             #+#    #+#             */
/*   Updated: 2024/01/02 00:08:35 by maroy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**rm_env_by_key(int index, char **env_pointer)
{
	char	*next_env;
	char	*tmp;
	int		i;

	i = index;
	if (i < ft_tablen(env_pointer))
	{
		while (env_pointer[i + 1] != NULL)
		{
			next_env = ft_strdup(env_pointer[i + 1]);
			tmp = env_pointer[i];
			env_pointer[i] = next_env;
			ft_free(tmp);
			i++;
		}
	}
	tmp = env_pointer[i];
	env_pointer[i] = 0;
	ft_free(tmp);
	return (env_pointer);
}

t_u8	unset_builtin(char **args, t_data *data)
{
	int	i;
	int	env_index;

	(void)data;
	i = -1;
	if (!args[1])
		return (KO);
	while (args[++i])
	{
		env_index = find_env_var_index(args[i], g_global->env_var);
		if (env_index != -1)
			g_global->env_var = rm_env_by_key(env_index, g_global->env_var);
		else
		{
			if (!is_valid_env_key(args[i]))
			{
				not_valid_id(args[i]);
				continue ;
			}
		}
	}
	return (OK);
}
