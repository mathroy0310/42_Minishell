/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maroy <maroy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 14:05:13 by maroy             #+#    #+#             */
/*   Updated: 2023/09/11 14:33:07 by maroy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

char	**remove_env_by_key(int index, char **env_pointer)
{
	char			*next_env;
	char			*pfree;
	register int	i;

	i = index;
	if (i < ft_tablen(env_pointer))
	{
		while (env_pointer[i + 1] != NULL)
		{
			next_env = ft_strdup(env_pointer[i + 1]);
			pfree = env_pointer[i];
			env_pointer[i] = next_env;
			free (pfree);
			i++;
		}
	}
	pfree = env_pointer[i];
	env_pointer[i] = 0;
	free (pfree);
	return (env_pointer);
}

/*
**  unset a bash environment variable
**  unset arg
**  unset arg1 arg2 *
*/

uint8_t	unset_builtin(char **args, t_data *data)
{
	int	i;
	int	env_index;
	int	env_index_;

	i = -1;
	if (!args[1])
		return (1);
	while (args[++i])
	{
		env_index = find_env(args[i], g_global->env_var);
		env_index_ = find_env(args[i], data->state->env_);
		if (env_index_ != -1)
			data->state->env_ = remove_env_by_key(env_index_, data->state->env_);
		if (env_index != -1)
			g_global->env_var = remove_env_by_key(env_index, g_global->env_var);
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