/* ************************************************************************** */
/*                                                                            */
/*                                                     ██   ██ ██████         */
/*   debug.c                                           ██   ██      ██        */
/*                                                     ███████  █████         */
/*   By: maroy <maroy@student.42.qc>                        ██ ██             */
/*                                                          ██ ███████.qc     */
/*   Created: 2023/08/21 16:03:34 by maroy                                    */
/*   Updated: 2023/10/17 16:42:35 by maroy            >(.)__ <(.)__ =(.)__    */
/*                                                     (___/  (___/  (___/    */
/* ************************************************************************** */

#include "minishell.h"

void	debug_print_tab(char **tab)
{
	int	i;

	if (DEBUG == 1)
	{
		i = -1;
		while (tab[++i])
			printf(ANSI_COLOR_BRIGHT_BLUE "DEBUG 🐞: tab[%d] -={ %s }=-", i,
				tab[i]);
		printf(ANSI_COLOR_RESET"\n");
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
				printf(ANSI_COLOR_BRIGHT_BLUE "DEBUG 🐞: cmd[%d]->argvs[%d] -={ \
					%s }=-\n", i, j, cmd[i].argvs[j]);
			printf(ANSI_COLOR_BRIGHT_BLUE "DEBUG 🐞: cmd[%d]->nbr_cmd -={ \
				%d }=-\n", i, cmd[i].nbr_cmd);
			printf(ANSI_COLOR_BRIGHT_BLUE "DEBUG 🐞: cmd[%d]->args_size -={ \
				%d }=-\n", i, cmd[i].args_size);
			printf(ANSI_COLOR_BRIGHT_BLUE "DEBUG 🐞: cmd[%d]->redir_nbr -={ \
				%d }=-\n", i, cmd[i].redir_nbr);
			debug_print_msg("-----------------------------------");
			printf(ANSI_COLOR_RESET"\n");
		}
	}
}

void	debug_print_string(char *msg, char *arg)
{
	if (DEBUG == 1)
	{
		printf(ANSI_COLOR_BRIGHT_BLUE "DEBUG 🐞: %s -={ %s }=-", msg, arg);
		printf(ANSI_COLOR_RESET"\n");
	}
}

void	debug_print_decimal(char *msg, int arg)
{
	if (DEBUG == 1)
	{
		printf(ANSI_COLOR_BRIGHT_BLUE "DEBUG 🐞: %s -={ %d }=-", msg, arg);
		printf(ANSI_COLOR_RESET"\n");
	}
}

void	debug_print_msg(char *msg)
{
	if (DEBUG == 1)
	{
		printf(ANSI_COLOR_BRIGHT_BLUE "DEBUG 🐞: -={ %s }=-", msg);
		printf(ANSI_COLOR_RESET"\n");
	}
}
