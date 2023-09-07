/* ************************************************************************** */
/*                                                                            */
/*                                                     ██   ██ ██████         */
/*   utils.c                                           ██   ██      ██        */
/*                                                     ███████  █████         */
/*   By: maroy <maroy@student.42.qc>                        ██ ██             */
/*                                                          ██ ███████.qc     */
/*   Created: 2023/09/01 16:38:29 by maroy                                    */
/*   Updated: 2023/09/07 13:10:55 by maroy            >(.)__ <(.)__ =(.)__    */
/*                                                     (___/  (___/  (___/    */
/* ************************************************************************** */

#include "../../../inc/minishell.h"
#include <stdbool.h>

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

	i = find_env(key, data->state->env_);
	if (i == -1)
	{
		i = 0;
		while (data->state->env_[i])
			i++;
		data->state->env_ = realloc_new_env(i, arg, data->state->env_);
	}
	else
	{
		i = find_env(key, data->state->env_);
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
	i = get_str_by_char(arg, '=');
	if (i == -1)
		return ;
	key = ft_substr(arg, 0, i);
	new_env(arg, key, data);
	free(key);
}

void	modify_env(char *arg, char *key)
{
	int		i;
	char	*new_value;
	char	*tmp;

	i = find_env(key, g_global->env_var);
	if (i == -1)
		return ;
	else
	{
		new_value = ft_strdup(arg);
		tmp = g_global->env_var[i];
		g_global->env_var[i] = new_value;
		free(tmp);
	}
}

void	print_sorted_env(char **sorted_env)
{
	int		i;
	int		j;
	bool	equ_sign;

	i = -1;
	while (sorted_env[++i])
	{
		j = 0;
		equ_sign = false;
		ft_putstr_fd("declare -x ", 1);
		while (sorted_env[i][j])
		{
			ft_putchar_fd(sorted_env[i][j], 1);
			if (sorted_env[i][j] == '=' && equ_sign)
			{
				ft_putchar_fd('"', 1);
				equ_sign = true;
			}
			j++;
		}
		if (equ_sign == true)
			ft_putendl_fd("\"", 1);
		else
			ft_putchar_fd('\n', 1);
	}
}

int	env_count(void)
{
	int	i;

	i = 0;
	while (g_global->env_var[i])
		i++;
	return (i);
}

char	**dup_env(void)
{
	char	**dup;
	int		i;

	i = env_count();
	dup = (char **)malloc(sizeof(char *) * (i + 1));
	if (!dup)
		return (NULL);
	dup[i] = 0;
	i--;
	while (i != -1)
	{
		dup[i] = g_global->env_var[i];
		i--;
	}
	return (dup);
}

void	sort_and_print(void)
{
	char	**dup;
	char	*tmp;
	int		i;
	int		j;

	dup = dup_env();
	i = 0;
	while (dup[i])
	{
		j = i + 1;
		while (dup[j])
		{
			if (ft_strcmp(dup[i], dup[j]) > 0)
			{
				tmp = dup[i];
				dup[i] = dup[j];
				dup[j] = tmp;
			}
			j++;
		}
		i++;
	}
	print_sorted_env(dup);
	free(dup);
}

int	find_env(char *key, char **env_pointer)
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

int	check_only_key(char *key)
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
