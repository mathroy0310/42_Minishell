/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_errors.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maroy <maroy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/09 00:45:18 by maroy             #+#    #+#             */
/*   Updated: 2023/12/09 00:59:22 by maroy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <dirent.h>

int	error_message(char *path)
{
	DIR	*dir;
	int	fd;
	int	ret;

	fd = open(path, O_RDONLY);
	dir = opendir(path);
	ft_putstr_err(ERR_PROMPT);
	ft_putstr_err(path);
	if (!ft_strchr(path, '/'))
		ft_putstr_errnl(": command not found");
	else if (fd < 0 && !dir)
		ft_putstr_errnl(": No such file or directory");
	else if (fd < 0 && dir)
		ft_putstr_errnl(": is a directory");
	else if (fd > 0 && !dir)
		ft_putstr_errnl(": Permission denied");
	if (!ft_strchr(path, '/') || (fd < 0 && !dir))
		ret = 127;
	else
		ret = 126;
	if (dir)
		closedir(dir);
	ft_close(fd);
	return (ret);
}

char	*check_dir(char *bin, char *cmd)
{
	DIR *dir;
	struct dirent *item;
	char *path;

	path = NULL;
	dir = opendir("bin");
	if (!dir)
		return (NULL);
	while ((item = readdir(dir)) != NULL)
	{
		if (!ft_strcmp(item->d_name, cmd))
		{
			path = path_join(bin, item->d_name);
			break ;
		}
	}
	closedir(dir);
	return (path);
}