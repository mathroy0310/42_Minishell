/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maroy <maroy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 18:00:20 by maroy             #+#    #+#             */
/*   Updated: 2024/01/02 00:52:58 by maroy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <dirent.h>

int	add_var_to_env(char *key, char *new_path)
{
	int		index;
	char	*tmp;
	char	*pfree;

	tmp = NULL;
	if (!key || !new_path)
		return (KO);
	index = find_env_var_index(key, g_global->env_var);
	if (index == -1)
		return (OK);
	else
	{
		tmp = ft_strjoin(key, "=");
		pfree = tmp;
		tmp = ft_strjoin(tmp, new_path);
		free(pfree);
		pfree = g_global->env_var[index];
		g_global->env_var[index] = tmp;
		free(pfree);
	}
	return (OK);
}

static int	move_to_dir(char *path)
{
	int		ret;
	char	*old_pwd;
	char	*tmp;

	old_pwd = get_env_var_by_key("PWD");
	add_var_to_env("OLDPWD", old_pwd);
	ret = chdir(path);
	tmp = get_pwd();
	if (!tmp && (!ft_strcmp(".", path) || !ft_strcmp("./", path)))
	{
		error_retrieving_cd();
		free(tmp);
		tmp = get_env_var_by_key("PWD");
		tmp = add_char_to_word(tmp, '/');
		old_pwd = tmp;
		tmp = ft_strjoin(tmp, path);
		free(old_pwd);
		add_var_to_env("PWD", tmp);
		g_global->exit_status = EXIT_FAILURE;
		free(tmp);
		return (EXIT_FAILURE);
	}
	add_var_to_env("PWD", tmp);
	free(tmp);
	return (ret);
}

static t_u8	change_dir(char *path, int i, char **argv)
{
	DIR	*dir;

	dir = opendir(path);
	if (!dir)
		return (error_path("cd", argv[i + 1], errno));
	else
	{
		closedir(dir);
		if (DEBUG)
			ft_debug_printf("path dans change_dir %s", path);
		if (move_to_dir(path) == -1)
			return (error_path("cd", argv[i + 1], errno));
	}
	return (OK);
}

static char	*cd_check_path(char **argv)
{
	char	*path;
	int		len;

	len = ft_tablen(argv);
	if (len == 1 || len > 2)
	{
		path = get_env_var_by_key("HOME");
		if (len > 2)
		{
			g_global->exit_status = EXIT_FAILURE;
			ft_putstr_err(FT_RED ERR_PROMPT);
			ft_putstr_errnl("cd: too many arguments" FT_COLOR_RESET);
			return (NULL);
		}
		else if (len == 1 && !path)
		{
			g_global->exit_status = EXIT_FAILURE;
			ft_putstr_err(FT_RED ERR_PROMPT);
			ft_putstr_errnl("cd: HOME not set" FT_COLOR_RESET);
			return (NULL);
		}
	}
	else
		path = argv[1];
	return (path);
}

t_u8	cd_builtin(char **argv)
{
	int		i;
	char	*path;
	char	*pwd;

	i = 0;
	g_global->exit_status = EXIT_SUCCESS;
	path = cd_check_path(argv);
	if (!path)
		return (KO);
	if (change_dir(path, i, argv))
		return (OK);
	pwd = get_env_var_by_key("PWD");
	add_var_to_env("PWD", pwd);
	ft_free(pwd);
	return (OK);
}
