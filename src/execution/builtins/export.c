/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maroy <maroy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/01 16:34:10 by maroy             #+#    #+#             */
/*   Updated: 2023/09/07 11:56:06 by maroy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

int	is_valid_env_key(char *arg)
{
	int	i;
	int	alpha;

	i = 0;
	alpha = 0;
	if (!ft_strcmp(arg, ""))
		return (0);
	if (arg == NULL || arg[0] == '=')
		return (0);
	while (arg[i] && arg[i] != '=')
	{
		if (ft_isalpha(arg[i]))
			alpha = 1;
		else
		{
			if (ft_isdigit(arg[i]) && !alpha)
				return (0);
			else if (!ft_isdigit(arg[i]) && arg[i] != '_')
				return (0);
		}
		i++;
	}
	return (1);
}

static void	set_new_env(char *arg)
{
	int		index;
	int		i;

	index = 0;
	i = -1;
	if (arg == NULL)
		return ;
	while (arg[++i])
		if (arg[i] == '=')
			index = 1;
	index = (env_count());
	g_global->env_var = realloc_new_env(index, arg, g_global->env_var);
}

static void	set_or_modify(char *arg)
{
	int		is_set;
	int		i;
	char	*key;
	int		just_key;

	just_key = 0;
	if (arg == NULL)
		return ;
	i = get_str_by_char(arg, '=');
	if (i == -1)
	{
		just_key = 1;
		i = ft_strlen(arg);
	}
	key = ft_substr(arg, 0, i);
	is_set = find_env(key, g_global->env_var);
	if (is_set == -1)
		set_new_env(arg);
	else
	{
		if (!just_key)
			modify_env(arg, key);
	}
	free (key);
}


uint8_t	export_builtin(char **args, t_data *data)
{
	int i;

	i = 0;
	g_global->exit_status = 0;
	if (!args[1])
	{
		sort_and_print();
		return (OK);
	}
	while (args[i++])
	{
		if (!is_valid_env_key(args[i]) && args[i] != NULL)
		{
			ft_putstr_fd("minishell: export: `", 2);
			ft_putstr_fd(args[i], 2);
			ft_putstr_fd("': not a valid identifier\n", 2);
			g_global->exit_status = 1;
			continue ;
		}
		set_or_modify(args[i]);
		add_to_env(args[i], data);
		debug_print_msg("export Success full");
	}
	return (OK);
}
