/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maroy <maroy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 14:05:13 by maroy             #+#    #+#             */
/*   Updated: 2023/12/08 20:02:02 by maroy            ###   ########.fr       */
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
			free(tmp);
			i++;
		}
	}
	tmp = env_pointer[i];
	env_pointer[i] = 0;
	free(tmp);
	return (env_pointer);
}

t_u8	unset_builtin(char **args, t_data *data)
{
	int i;
	int env_index;
	int env_index_;

	i = -1;
	if (!args[1])
		return (KO);
	while (args[++i])
	{
		env_index = find_env_var_index(args[i], g_global->env_var);
		env_index_ = find_env_var_index(args[i], data->state->env_);
		if (env_index_ != -1)
			data->state->env_ = rm_env_by_key(env_index_, data->state->env_);
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