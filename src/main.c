/* ************************************************************************** */
/*                                                                            */
/*                                                     ██   ██ ██████         */
/*   main.c                                            ██   ██      ██        */
/*                                                     ███████  █████         */
/*   By: maroy <maroy@student.42.qc>                        ██ ██             */
/*                                                          ██ ███████.qc     */
/*   Created: 2023/07/14 21:56:43 by maroy                                    */
/*   Updated: 2023/08/16 19:24:53 by maroy            >(.)__ <(.)__ =(.)__    */
/*                                                     (___/  (___/  (___/    */
/* ************************************************************************** */

#include "../inc/minishell.h"

/*
	TODO parsing -> cmds -> shell redirection -> flags - quotes - env - pipes

	exec_pwd()
	exec_env()
	get_env_content()

*/

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
		if (ft_strlen(buffer) == 0 || using_valid_characters(buffer, minishell))
			continue ;
        if (init_token(minishell, buffer) == 0)
            continue ; 
		//status = exec_cmd(buffer, minishell);
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
		ft_putstr_fd("minishell: init failed\n", STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	minishell.exit_status = master(&minishell);

	tcsetattr(STDIN_FILENO, TCSANOW, &term);

	return (minishell.exit_status);
}
