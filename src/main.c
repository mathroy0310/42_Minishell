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

int8_t read_input(char *buffer, t_minishell *minishell)
{
    int i;

	if (handle_tokens(buffer, minishell))
		return (EXIT_FAILURE);
    i = -1;
	DEBUG_print_tab(minishell->argv);
    while (minishell->argv[++i])
    {
        if (ft_strncmp(minishell->argv[i], "<<", 3) == 0 && minishell->argv[i + 1])
        {
            DEBUG_print_msg("here doc", NULL);
        } 
    }
    return (EXIT_SUCCESS);
    
}

int8_t	master(char **envp)
{
	char	buffer[BUFFER_SIZE];
	int		status;
	t_minishell *minishell;

	//char 	*tok;
	minishell = init_env(envp);
	signal(SIGQUIT, SIG_IGN);
	status = 1;
	while (status)
	{
		signal(SIGINT, sig_interrupt);
		if (take_input(buffer, minishell))
			break ;
		if (ft_strlen(buffer) == 0 || using_valid_characters(buffer, minishell) || read_input(buffer, minishell))
			continue ;
		ft_free_tab(minishell->argv);
	}
	destroy_program(minishell);
	return (EXIT_SUCCESS);
}

int	main(int argc, char **argv, char **envp)
{
	struct termios	term;

	if (argc > 1 && argv)
	{
		print_msg_error("no arguments needed");
		return (EXIT_FAILURE);
	}
	
	// on pourrait checker pour le -c flag ici
	// pour command line execution ca serait comique
	tcgetattr(STDIN_FILENO, &term);
	using_history();
	master(envp);

	tcsetattr(STDIN_FILENO, TCSANOW, &term);
	return (EXIT_SUCCESS);
}
