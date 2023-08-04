/* ************************************************************************** */
/*                                                                            */
/*                                                     ██   ██ ██████         */
/*   main.c                                            ██   ██      ██        */
/*                                                     ███████  █████         */
/*   By: maroy <maroy@student.42.qc>                        ██ ██             */
/*                                                          ██ ███████.qc     */
/*   Created: 2023/07/14 21:56:43 by maroy                                    */
/*   Updated: 2023/08/04 13:36:27 by maroy            >(.)__ <(.)__ =(.)__    */
/*                                                     (___/  (___/  (___/    */
/* ************************************************************************** */

#include "../inc/minishell.h"

/*
	TODO parsing -> cmds -> shell redirection -> flags - quotes - env - pipes
*/

int8_t master(t_minishell *minishell)
{
    char* input;
	
	while (1)
    {
		//! ca vrm pas rapport ici
		input = readline("minishell$ ");
        if (input == NULL)
		{
			ft_putstr_fd("exit", STDOUT_FILENO);
			return (EXIT_SUCCESS);
		}
    	add_history(input);	
		if (strcmp(input, "exit") == 0)
			break;
		if (strcmp(input, "pwd") == 0)
		{
			exec_pwd();
			master(minishell);
		}
		if (strcmp(input, "env") == 0)
		{
			exec_env(minishell->env);
			master(minishell);
		}
        free(input);
		//! 
    }
	return (EXIT_SUCCESS);
}

int main(int argc, char **argv, char **envp)
{
	t_minishell minishell;
	struct termios	term;

	(void)argc;
	(void)argv; // on pourrait checker pour le -c flag ici
	tcgetattr(STDIN_FILENO, &term);

    using_history();
	if (init(&minishell, envp))
	{
		ft_putstr_fd("minishell: init failed\n", STDERR_FILENO);
		return (EXIT_FAILURE);		
	}
	minishell.exit_status = master(&minishell);
		
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
	
    return (minishell.exit_status);
}
