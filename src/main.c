/* ************************************************************************** */
/*                                                                            */
/*                                                     ██   ██ ██████         */
/*   main.c                                            ██   ██      ██        */
/*                                                     ███████  █████         */
/*   By: maroy <maroy@student.42.qc>                        ██ ██             */
/*                                                          ██ ███████.qc     */
/*   Created: 2023/07/14 21:56:43 by maroy                                    */
/*   Updated: 2023/07/31 17:54:49 by maroy            >(.)__ <(.)__ =(.)__    */
/*                                                     (___/  (___/  (___/    */
/* ************************************************************************** */

#include "../inc/minishell.h"

/*
	TODO parsing -> cmds -> shell redirection -> flags - quotes - env - pipes
*/

signed char master()
{
    char* input;
	
	while (1)
    {
        input = readline(PROMPT);
        if (*input)
        {
            add_history(input);
            printf("<DEBUG> : You entered: %s\n", input);
            write_history(HISTORY_FILE);
        }
        free(input);
		if (0 == strcmp(input, "exit"))
			break ;
    }
	return 0;
}

int main(void)
{
	t_minishell minishell;
	
	init(&minishell);
    if ( 0 != read_history(HISTORY_FILE))
	{
		printf(ERROR_RL_H);
		return (EXIT_FAILURE);
	}
    using_history();
	minishell.exit_status = master();
	// juste pour etre sur que le fichier est bien ecrit
	write_history(HISTORY_FILE);
    return (minishell.exit_status);
}