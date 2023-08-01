/* ************************************************************************** */
/*                                                                            */
/*                                                     ██   ██ ██████         */
/*   main.c                                            ██   ██      ██        */
/*                                                     ███████  █████         */
/*   By: maroy <maroy@student.42.qc>                        ██ ██             */
/*                                                          ██ ███████.qc     */
/*   Created: 2023/07/14 21:56:43 by maroy                                    */
/*   Updated: 2023/08/01 15:05:52 by maroy            >(.)__ <(.)__ =(.)__    */
/*                                                     (___/  (___/  (___/    */
/* ************************************************************************** */

#include "../inc/minishell.h"

/*
	TODO parsing -> cmds -> shell redirection -> flags - quotes - env - pipes
*/

int8_t master()
{
    char* input;
	
	while (1)
    {
		//! ca vrm pas rapport ici
		input = readline("minishell$ ");
        if (input != NULL)
        {
            add_history(input);
        }
            //printf("<DEBUG> : You entered: %s\n", input);
		else
		{
			ft_putstr_fd("exit\n", 1);
			return (EXIT_SUCCESS);
		}
        free(input);
		if (0 == strcmp(input, "exit"))
			return (EXIT_SUCCESS);
		//! 
    }
	return (EXIT_SUCCESS);
}

int main(void)
{
	t_minishell minishell;
	
    using_history();
	init(&minishell);
	minishell.exit_status = master();
	// juste pour etre sur que le fichier est bien ecrit
    return (minishell.exit_status);
}
