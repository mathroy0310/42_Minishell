/* ************************************************************************** */
/*                                                                            */
/*                                                     ██   ██ ██████         */
/*   main.c                                            ██   ██      ██        */
/*                                                     ███████  █████         */
/*   By: maroy <maroy@student.42.qc>                        ██ ██             */
/*                                                          ██ ███████.qc     */
/*   Created: 2023/07/14 21:56:43 by maroy                                    */
/*   Updated: 2023/08/24 20:14:49 by maroy            >(.)__ <(.)__ =(.)__    */
/*                                                     (___/  (___/  (___/    */
/* ************************************************************************** */

#include "../inc/minishell.h"

/*
	TODO parsing -> cmds -> shell redirection -> flags - quotes - env - pipes

	exec_pwd()
	exec_env()
	get_env_content()

*/


int8_t read_input(char *buffer, t_minishell *minishell)
{
    int i;

    if (init_token(minishell, buffer) == EXIT_FAILURE)
        return (EXIT_FAILURE);
    i = -1;
    while (minishell->argv[++i])
    {
        if (ft_strncmp(minishell->argv[i], "<<", 3) == 0 && minishell->argv[i + 1])
        {
            DEBUG_print_msg("here doc", NULL);
        } 
    }
    return (EXIT_SUCCESS);
    
}

int8_t	master(t_minishell *minishell)
{
	char	buffer[BUFFER_SIZE];
	int		status;

	//char 	*tok;
	status = 1;
	signal(SIGQUIT, SIG_IGN);
	while (status)
	{
		signal(SIGINT, sig_interrupt);
		if (take_input(buffer))
			break ;
		if (ft_strlen(buffer) == 0 || using_valid_characters(buffer, minishell) || read_input(buffer, minishell))
			continue ;
	}
	return (EXIT_SUCCESS);
}

int	main(int argc, char **argv, char **envp)
{
	t_minishell		minishell;
	struct termios	term;

	(void)argc;
	(void)argv; 
	// on pourrait checker pour le -c flag ici
	// pour command line execution ca serait comique
	tcgetattr(STDIN_FILENO, &term);
	using_history();

	if (init(&minishell, envp))
	{
		print_msg_error("init failed");
		return (EXIT_FAILURE);
	}
	minishell.exit_status = master(&minishell);

	tcsetattr(STDIN_FILENO, TCSANOW, &term);

	return (minishell.exit_status);
}
