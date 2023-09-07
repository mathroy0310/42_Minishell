/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maroy <maroy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 16:03:34 by maroy             #+#    #+#             */
/*   Updated: 2023/09/07 11:52:35 by maroy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	debug_print_tab(char **tab)
{
	int	i;

	if (DEBUG == 1)
	{
		i = -1;
		while (tab[++i])
			printf(BLUE "DEBUG 🐞: tab[%d] -={ %s }=-\n" DEFAULT, i, tab[i]);
	}
}

void	debug_print_cmd(t_cmd *cmd)
{
	int	i;
	int	j;

	if (DEBUG == 1)
	{
		i = -1;
		while (++i != cmd->nbr_cmd)
		{
			j = -1;
			while (cmd[i].argvs[++j])
				printf(BLUE "DEBUG 🐞: cmd[%d]->argvs[%d] -={ %s }=-\n" DEFAULT,
						i, j, cmd[i].argvs[j]);
			printf(BLUE "DEBUG 🐞: cmd[%d]->nbr_cmd -={ %d }=-\n" DEFAULT, i,
					cmd[i].nbr_cmd);
			printf(BLUE "DEBUG 🐞: cmd[%d]->args_size -={ %d }=-\n" DEFAULT, i,
					cmd[i].args_size);
			printf(BLUE "DEBUG 🐞: cmd[%d]->redir_nbr -={ %d }=-\n" DEFAULT, i,
					cmd[i].redir_nbr);
			debug_print_msg("-----------------------------------");
		}
	}
}

void	debug_print_string(char *msg, char *arg)
{
	if (DEBUG == 1)
		printf(BLUE "DEBUG 🐞: %s -={ %s }=-\n" DEFAULT, msg, arg);
}

void	debug_print_decimal(char *msg, int arg)
{
	if (DEBUG == 1)
		printf(BLUE "DEBUG 🐞: %s -={ %d }=-\n" DEFAULT, msg, arg);
}

void	debug_print_char(char *msg, char arg)
{
	if (DEBUG == 1)
		printf(BLUE "DEBUG 🐞: %s -={ %c }=-\n" DEFAULT, msg, arg);
}

void	debug_print_msg(char *msg)
{
	if (DEBUG == 1)
		printf(BLUE "DEBUG 🐞: -={ %s }=- \n" DEFAULT, msg);
}
