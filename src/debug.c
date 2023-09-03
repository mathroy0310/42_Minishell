/* ************************************************************************** */
/*                                                                            */
/*                                                     ██   ██ ██████         */
/*   debug.c                                           ██   ██      ██        */
/*                                                     ███████  █████         */
/*   By: maroy <maroy@student.42.qc>                        ██ ██             */
/*                                                          ██ ███████.qc     */
/*   Created: 2023/08/21 16:03:34 by maroy                                    */
/*   Updated: 2023/09/02 18:51:58 by maroy            >(.)__ <(.)__ =(.)__    */
/*                                                     (___/  (___/  (___/    */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	debug_print_tab(char **tab)
{
	int	i;

	if (DEBUG == 1)
	{
		i = -1;
		while (tab[++i])
			printf(BLUE "debug 🐞: tab[%d] -={ %s }=-\n" DEFAULT, i, tab[i]);
	}
}

void	debug_print_string(char *msg, char *arg)
{
	if (DEBUG == 1)
		printf(BLUE "debug 🐞: %s -={ %s }=-\n" DEFAULT, msg, arg);
}

void	debug_print_decimal(char *msg, int arg)
{
	if (DEBUG == 1)
		printf(BLUE "debug 🐞: %s -={ %d }=-\n" DEFAULT, msg, arg);
}

void	debug_print_char(char *msg, char arg)
{
	if (DEBUG == 1)
		printf(BLUE "debug 🐞: %s -={ %c }=-\n" DEFAULT, msg, arg);
}

void	debug_print_msg(char *msg)
{
	if (DEBUG == 1)
		printf(BLUE "debug 🐞: -={ %s }=- \n" DEFAULT, msg);
}
