/* ************************************************************************** */
/*                                                                            */
/*                                                     ██   ██ ██████         */
/*   debug.c                                           ██   ██      ██        */
/*                                                     ███████  █████         */
/*   By: maroy <maroy@student.42.qc>                        ██ ██             */
/*                                                          ██ ███████.qc     */
/*   Created: 2023/08/21 16:03:34 by maroy                                    */
/*   Updated: 2023/08/23 17:05:42 by maroy            >(.)__ <(.)__ =(.)__    */
/*                                                     (___/  (___/  (___/    */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	DEBUG_print_token_type(t_token *tokens)
{
	if (tokens->type == CMD)
		printf("DEBUG : token type -={ %s }=-\n", "CMD");
	else if (tokens->type == FLAG)
		printf("DEBUG : token type -={ %s }=-\n", "FLAG");
	else if (tokens->type == ARG)
		printf("DEBUG : token type -={ %s }=-\n", "ARG");
	else if (tokens->type == PIPE)
		printf("DEBUG : token type -={ %s }=-\n", "PIPE");
	else if (tokens->type == REDIRECT)
		printf("DEBUG : token type -={ %s }=-\n", "REDIRECT");
	else if (tokens->type == QUOTED_STRING)
		printf("DEBUG : token type -={ %s }=-\n", "QUOTED_STRING");
	else if (tokens->type == ENV_VAR)
		printf("DEBUG : token type -={ %s }=-\n", "ENV_VAR");
	else if (tokens->type == END)
		printf("DEBUG : token type -={ %s }=-\n", "END");
	else
		printf("DEBUG : token type -={ %s }=-\n", "UNKNOWN");
}

void	DEBUG_print_msg(char *msg, char *arg)
{
	printf("DEBUG : %s -={ %s }=-\n", msg, arg);
}
