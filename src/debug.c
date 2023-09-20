/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maroy <maroy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 16:03:34 by maroy             #+#    #+#             */
/*   Updated: 2023/09/19 23:09:22 by maroy            ###   ########.fr       */
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
			printf(ANSI_COLOR_BRIGHT_BLUE "DEBUG 🐞: tab[%d] -={ %s }=-", i, tab[i]);
		printf("\n");	
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
				printf(ANSI_COLOR_BRIGHT_BLUE "DEBUG 🐞: cmd[%d]->argvs[%d] -={ %s }=-\n",
					i, j, cmd[i].argvs[j]);
			printf(ANSI_COLOR_BRIGHT_BLUE "DEBUG 🐞: cmd[%d]->nbr_cmd -={ %d }=-\n", i,
				cmd[i].nbr_cmd);
			printf(ANSI_COLOR_BRIGHT_BLUE "DEBUG 🐞: cmd[%d]->args_size -={ %d }=-\n", i,
				cmd[i].args_size);
			printf(ANSI_COLOR_BRIGHT_BLUE "DEBUG 🐞: cmd[%d]->redir_nbr -={ %d }=-\n", i,
				cmd[i].redir_nbr);
			debug_print_msg("-----------------------------------");
			printf("\n");	
		}
	}
}

void	debug_print_string(char *msg, char *arg)
{
	if (DEBUG == 1)
	{
		printf(ANSI_COLOR_BRIGHT_BLUE "DEBUG 🐞: %s -={ %s }=-", msg, arg);
		printf("\n");	
	}
}

void	debug_print_decimal(char *msg, int arg)
{
	if (DEBUG == 1)
	{
		printf(ANSI_COLOR_BRIGHT_BLUE "DEBUG 🐞: %s -={ %d }=-", msg, arg);
		printf("\n");	
	}
}

void	debug_print_char(char *msg, char arg)
{
	if (DEBUG == 1)
	{
		printf(ANSI_COLOR_BRIGHT_BLUE "DEBUG 🐞: %s -={ %c }=-", msg, arg);
		printf("\n");
	}
}

void	debug_print_msg(char *msg)
{
	if (DEBUG == 1)
	{
		printf(ANSI_COLOR_BRIGHT_BLUE "DEBUG 🐞: -={ %s }=-", msg);
		printf("\n");
	}
}
