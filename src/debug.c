/* ************************************************************************** */
/*                                                                            */
/*                                                     ██   ██ ██████         */
/*   debug.c                                           ██   ██      ██        */
/*                                                     ███████  █████         */
/*   By: maroy <maroy@student.42.qc>                        ██ ██             */
/*                                                          ██ ███████.qc     */
/*   Created: 2023/08/21 16:03:34 by maroy                                    */
/*   Updated: 2023/08/24 20:37:23 by maroy            >(.)__ <(.)__ =(.)__    */
/*                                                     (___/  (___/  (___/    */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	DEBUG_print_token_type(t_token *tokens)
{
	if (tokens->type == CMD)
		printf(BLUE "DEBUG 🐞 : token type -={ %s }=-\n" DEFAULT, "CMD");
	else if (tokens->type == FLAG)
		printf(BLUE "DEBUG 🐞: token type -={ %s }=-\n" DEFAULT, "FLAG");
	else if (tokens->type == ARG)
		printf(BLUE "DEBUG 🐞: token type -={ %s }=-\n" DEFAULT, "ARG");
	else if (tokens->type == PIPE)
		printf(BLUE "DEBUG 🐞: token type -={ %s }=-\n" DEFAULT, "PIPE");
	else if (tokens->type == REDIRECT)
		printf(BLUE "DEBUG 🐞: token type -={ %s }=-\n" DEFAULT, "REDIRECT");
	else if (tokens->type == S_QUOTED_STRING)
		printf(BLUE "DEBUG 🐞: token type -={ %s }=-\n" DEFAULT,
			"S_QUOTED_STRING");
	else if (tokens->type == D_QUOTED_STRING)
		printf(BLUE "DEBUG 🐞: token type -={ %s }=-\n" DEFAULT,
			"D_QUOTED_STRING");
	else if (tokens->type == ENV_VAR)
		printf(BLUE "DEBUG 🐞: token type -={ %s }=-\n" DEFAULT, "ENV_VAR");
	else if (tokens->type == END)
		printf(BLUE "DEBUG 🐞: token type -={ %s }=-\n" DEFAULT, "END");
	else
		printf(BLUE "DEBUG 🐞: token type -={ %s }=-\n" DEFAULT, "UNKNOWN");
}

void	DEBUG_print_tab(char **tab)
{
    int	i;

    i = -1;
    while (tab[++i])
        printf(BLUE "DEBUG 🐞: tab[%d] -={ %s }=-\n" DEFAULT, i, tab[i]);
}

void	DEBUG_print_msg(char *msg, char *arg)
{
	printf(BLUE "DEBUG 🐞: %s -={ %s }=-\n" DEFAULT, msg, arg);
}
