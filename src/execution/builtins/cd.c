/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maroy <maroy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 18:00:20 by maroy             #+#    #+#             */
/*   Updated: 2023/11/25 17:23:55 by maroy            ###   ########.fr       */
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
		debug_print_string("path dans change_dir", path);
		if (move_to_dir(path) == -1)
			return (error_path("cd", argv[i + 1], errno));
	}
	return (OK);
}

static t_u8	exec_cd(char *path, int i, char **argv)
{
	char	*pwd;

	if (change_dir(path, i, argv) == OK)
		return (OK);
	pwd = get_env_var_by_key("PWD");
	add_var_to_env("PWD", pwd);
	free(pwd);
	return (KO);
}

t_u8	cd_builtin(char **argv)
{
	char	*path;
	int		i;

	i = 0;
	g_global->exit_status = EXIT_SUCCESS;
	if (argv[i + 1] == NULL)
	{
		path = get_env_var_by_key("HOME");
		if (path == NULL)
		{
			g_global->exit_status = EXIT_FAILURE;
			ft_putstr_err(ANSI_COLOR_BRIGHT_RED ERR_PROMPT "cd:");
			ft_putstr_err(" HOME not set");
			ft_putstr_errnl(ANSI_COLOR_RESET);
			return (KO);
		}
		if (!ft_strcmp(path, ""))
			return (KO);
	}
	else if (ft_strncmp(argv[i + 1], "-", 2) == 0)
		path = get_env_var_by_key("OLDPWD");
	else
		path = argv[i + 1];
	exec_cd(path, i, argv);
	return (OK);
}
