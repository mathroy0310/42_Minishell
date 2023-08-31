/* ************************************************************************** */
/*                                                                            */
/*                                                     ██   ██ ██████         */
/*   debug.c                                           ██   ██      ██        */
/*                                                     ███████  █████         */
/*   By: maroy <maroy@student.42.qc>                        ██ ██             */
/*                                                          ██ ███████.qc     */
/*   Created: 2023/08/21 16:03:34 by maroy                                    */
/*   Updated: 2023/08/30 19:32:40 by maroy            >(.)__ <(.)__ =(.)__    */
/*                                                     (___/  (___/  (___/    */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	DEBUG_print_tab(char **tab)
{
    if (DEBUG == 1)
    {
        int	i;

        i = -1;
        while (tab[++i])
            printf(BLUE "DEBUG 🐞: tab[%d] -={ %s }=-\n" DEFAULT, i, tab[i]);
    }
}
void	DEBUG_print_string(char *msg, char *arg)
{
    if (DEBUG == 1)
    {
	    printf(BLUE "DEBUG 🐞: %s -={ %s }=-\n" DEFAULT, msg, arg);
    }
    
}

void	DEBUG_print_decimal(char *msg, int arg)
{
    if (DEBUG == 1)
    {
	    printf(BLUE "DEBUG 🐞: %s -={ %d }=-\n" DEFAULT, msg, arg);
    }
}

void	DEBUG_print_char(char *msg, char arg)
{
    if (DEBUG == 1)
    {
    	printf(BLUE "DEBUG 🐞: %s -={ %c }=-\n" DEFAULT, msg, arg);
    }
}


void	DEBUG_print_msg(char *msg)
{
    if (DEBUG == 1)
    {
	    printf(BLUE "DEBUG 🐞: -={ %s }=- \n" DEFAULT, msg);
    }
}
