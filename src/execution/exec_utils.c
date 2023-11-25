/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maroy <maroy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 15:24:41 by maroy             #+#    #+#             */
/*   Updated: 2023/11/24 12:33:36 by maroy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_env_var_by_key(const char *key)
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

static int8_t	check_only_key(const char *key)
{
	int	i;

	i = -1;
	if (!key)
		return (-1);
	while (g_global->env_var[++i])
	{
		if (!ft_strcmp(g_global->env_var[i], key))
			return (i);
	}
	return (-1);
}

int8_t	find_env_var_index(const char *key, char **env_pointer)
{
	int		index;
	char	*sub_env;
	int		i;

	i = -1;
	if (!key)
		return (-1);
	while (env_pointer[++i])
	{
		index = get_str_by_char(env_pointer[i], '=');
		if (index == -1)
			index = ft_strlen(env_pointer[i]);
		else
		{
			sub_env = ft_substr(env_pointer[i], 0, index);
			if (sub_env != NULL && ft_strequal(key, sub_env))
			{
				free(sub_env);
				return (i);
			}
			free(sub_env);
		}
	}
	return (check_only_key(key));
}

char	*find_path(char *cmd, char **path)
{
	char	*temp;
	char	*possible_path;
	int		i;
	int		fd;

	i = -1;
	fd = 0;
	if (path == NULL)
		return (NULL);
	while (path[++i])
	{
		temp = ft_strjoin(path[i], "/");
		possible_path = ft_strjoin(temp, cmd);
		fd = open(possible_path, O_RDONLY);
		if (fd >= 0)
		{
			free(temp);
			close(fd);
			return (possible_path);
		}
	}
	close(fd);
	free(temp);
	free(possible_path);
	return (NULL);
}
