/* ************************************************************************** */
/*                                                                            */
/*                                                     ██   ██ ██████         */
/*   cd.c                                              ██   ██      ██        */
/*                                                     ███████  █████         */
/*   By: maroy <maroy@student.42.qc>                        ██ ██             */
/*                                                          ██ ███████.qc     */
/*   Created: 2023/09/12 18:00:20 by maroy                                    */
/*   Updated: 2023/09/14 18:47:27 by maroy            >(.)__ <(.)__ =(.)__    */
/*                                                     (___/  (___/  (___/    */
/* ************************************************************************** */

#include "../../../inc/minishell.h"
#include <dirent.h>

static int	add_var_to_env(char *key, char *new_path)
{
	int		index;
	char	*tmp;
	char	*pfree;

	tmp = NULL;
	if (!key || !new_path)
		return (KO);
	index = find_env(key, g_global->env_var);
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

	debug_print_string("path dans move_to_dir = ", path);
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
		g_global->exit_status = 0;
		free(tmp);
		return (1);
	}
	add_var_to_env("PWD", tmp);
	free(tmp);
	return (ret);
}

static uint8_t	change_dir(char *path, int i, char **argv)
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

static uint8_t	exec_cd(char *path, int i, char **argv)
{
	char	*pwd;

	if (change_dir(path, i, argv) == OK)
		return (OK);
	pwd = get_env_var_by_key("PWD");
	add_var_to_env("PWD", pwd);
	free(pwd);
	return (KO);
}

int8_t	cd_builtin(char **argv)
{
	char	*path;
	int		i;

	i = 0;
	g_global->exit_status = 0;
	if (argv[i + 1] == NULL)
	{
		path = get_env_var_by_key("HOME");
		if (path == NULL)
		{
			g_global->exit_status = 1;
			ft_putstr_fd(RED "minishell: cd:", STDERR_FILENO);
			ft_putstr_fd(" HOME not set", STDERR_FILENO);
			ft_putendl_fd(DEFAULT, STDERR_FILENO);
			return (-1);
		}
		if (!ft_strcmp(path, ""))
			return (KO);
	}
	else if (ft_strncmp(argv[i + 1], "-", 2) == 0)
		path = get_env_var_by_key("OLDPWD");
	else
		path = argv[i + 1];
	exec_cd(path, i, argv);
	return (KO);
}
