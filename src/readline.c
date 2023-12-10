/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maroy <maroy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 22:08:58 by maroy             #+#    #+#             */
/*   Updated: 2023/12/09 19:24:22 by maroy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*check_line(char *buff)
{
	if (!buff)
	{
		quit_minishell(buff);
		return ("break");
	}
	else if (buff[0] == '\0')
	{
		ft_free(buff);
		return ("continue");
	}
	else
		return (buff);
}

void	use_history(void)
{
	int	fd;

	fd = open(HISTORY_FILE, O_CREAT, S_IRUSR | S_IWUSR);
	close(fd);
	using_history();
	read_history(HISTORY_FILE);
}
