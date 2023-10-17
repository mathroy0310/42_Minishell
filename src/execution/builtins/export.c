/* ************************************************************************** */
/*                                                                            */
/*                                                     ██   ██ ██████         */
/*   export.c                                          ██   ██      ██        */
/*                                                     ███████  █████         */
/*   By: maroy <maroy@student.42.qc>                        ██ ██             */
/*                                                          ██ ███████.qc     */
/*   Created: 2023/09/01 16:34:10 by maroy                                    */
/*   Updated: 2023/10/17 16:43:43 by maroy            >(.)__ <(.)__ =(.)__    */
/*                                                     (___/  (___/  (___/    */
/* ************************************************************************** */

#include "minishell.h"

uint8_t	is_valid_env_key(char *arg)
{
	int		i;
	bool	is_alnum;

	i = 0;
	if (!ft_strcmp(arg, ""))
		return (KO);
	if (arg == NULL || arg[0] == '=')
		return (KO);
	while (arg[i] && arg[i] != '=')
	{
		is_alnum = false;
		if (ft_isalnum(arg[i]) == OK)
			is_alnum = true;
		else
			if (is_alnum == false && arg[i] != '_')
				return (KO);
		i++;
	}
	return (OK);
}

static void	set_new_env(char *arg)
{
	int	index;
	int	i;

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
		just_key = OK;
		i = ft_strlen(arg);
	}
	key = ft_substr(arg, 0, i);
	is_set = find_env_var_index(key, g_global->env_var);
	if (is_set == -1)
		set_new_env(arg);
	else
	{
		if (just_key == KO)
			modify_env(arg, key);
	}
	free(key);
}

uint8_t	export_builtin(char **args, t_data *data)
{
	int	i;

	i = 0;
	g_global->exit_status = EXIT_SUCCESS;
	if (!args[1])
	{
		sort_and_print();
		return (OK);
	}
	while (args[i++])
	{
		if (!is_valid_env_key(args[i]) && args[i] != NULL)
		{
			ft_putstr_fd(ANSI_COLOR_BRIGHT_RED \
			ERR_PROMPT "export: `", STDERR_FILENO);
			ft_putstr_fd(args[i], STDERR_FILENO);
			ft_putstr_fd("': not a valid identifier", STDERR_FILENO);
			ft_putendl_fd(ANSI_COLOR_RESET, STDERR_FILENO);
			g_global->exit_status = EXIT_FAILURE;
			continue ;
		}
		set_or_modify(args[i]);
		add_to_env(args[i], data);
	}
	return (OK);
}
