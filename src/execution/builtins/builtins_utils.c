/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maroy <maroy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/01 16:38:29 by maroy             #+#    #+#             */
/*   Updated: 2024/01/02 00:16:08 by maroy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_old_env(char **env_pointer)
{
	int	i;

	i = 0;
	while (env_pointer[i])
	{
		free(env_pointer[i]);
		env_pointer[i] = NULL;
		i++;
	}
	free(env_pointer);
	env_pointer = NULL;
}

char	**realloc_new_env(int env_num, char *arg, char **env_pointer)
{
	char	**new_env;
	int		i;

	i = 0;
	new_env = (char **)malloc(sizeof(char *) * (env_num + 2));
	if (!new_env)
		return (NULL);
	while (env_pointer[i])
	{
		new_env[i] = ft_strdup(env_pointer[i]);
		i++;
	}
	new_env[i] = ft_strdup(arg);
	new_env[env_num + 1] = 0;
	free_old_env(env_pointer);
	return (new_env);
}

void	new_env(char *arg, char *key, t_data *data)
{
	int		i;
	char	*new_value;
	char	*tmp;

	i = find_env_var_index(key, data->state->env_);
	if (i == -1)
	{
		i = 0;
		while (data->state->env_[i])
			i++;
		data->state->env_ = realloc_new_env(i, arg, data->state->env_);
	}
	else
	{
		i = find_env_var_index(key, data->state->env_);
		if (i == -1)
			return ;
		else
		{
			new_value = ft_strdup(arg);
			tmp = data->state->env_[i];
			data->state->env_[i] = new_value;
			free(tmp);
		}
	}
}

void	add_to_env(char *arg, t_data *data)
{
	int		i;
	char	*key;

	if (arg == NULL)
		return ;
	i = get_str_from_char(arg, '=', FALSE);
	if (i == -1)
		return ;
	key = ft_substr(arg, 0, i);
	new_env(arg, key, data);
	free(key);
}

int	env_count(void)
{
	int	i;

	i = 0;
	while (g_global->env_var[i])
		i++;
	return (i);
}
