/* ************************************************************************** */
/*                                                                            */
/*                                                     ██   ██ ██████         */
/*   debug.c                                           ██   ██      ██        */
/*                                                     ███████  █████         */
/*   By: maroy <maroy@student.42.qc>                        ██ ██             */
/*                                                          ██ ███████.qc     */
/*   Created: 2023/08/21 16:03:34 by maroy                                    */
/*   Updated: 2023/10/28 19:03:11 by maroy            >(.)__ <(.)__ =(.)__    */
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
			ft_printf(ANSI_COLOR_BRIGHT_BLUE "DEBUG 🐞: tab[%d] -={ %s }=-", i,
				tab[i]);
		ft_putstr_nl(ANSI_COLOR_RESET);
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
			if (cmd[i].argvs)
			{
				while (cmd[i].argvs[++j])
					ft_printf(ANSI_COLOR_BRIGHT_BLUE "DEBUG 🐞: cmd[%d]->argvs[%d] -={ \
						%s }=-\n", i, j, cmd[i].argvs[j]);
			}
			ft_printf(ANSI_COLOR_BRIGHT_BLUE "DEBUG 🐞: cmd[%d]->nbr_cmd -={ \
				%d }=-\n", i, cmd[i].nbr_cmd);
			ft_printf(ANSI_COLOR_BRIGHT_BLUE "DEBUG 🐞: cmd[%d]->args_size -={ \
				%d }=-\n", i, cmd[i].args_size);
			ft_printf(ANSI_COLOR_BRIGHT_BLUE "DEBUG 🐞: cmd[%d]->redir_nbr -={ \
				%d }=-\n", i, cmd[i].redir_nbr);
			debug_print_msg("-----------------------------------");
			ft_putstr_nl(ANSI_COLOR_RESET);
		}
	}
}

void	debug_print_string(char *msg, char *arg)
{
	if (DEBUG == 1)
	{
		ft_printf(ANSI_COLOR_BRIGHT_BLUE "DEBUG 🐞: %s -={ %s }=-", msg, arg);
		ft_putstr_nl(ANSI_COLOR_RESET);
	}
}

void	debug_print_decimal(char *msg, int arg)
{
	if (DEBUG == 1)
	{
		ft_printf(ANSI_COLOR_BRIGHT_BLUE "DEBUG 🐞: %s -={ %d }=-", msg, arg);
		ft_putstr_nl(ANSI_COLOR_RESET);
	}
}

void	debug_print_msg(char *msg)
{
	if (DEBUG == 1)
	{
		ft_printf(ANSI_COLOR_BRIGHT_BLUE "DEBUG 🐞: -={ %s }=-", msg);
		ft_putstr_nl(ANSI_COLOR_RESET);
	}
}
