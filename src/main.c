/* ************************************************************************** */
/*                                                                            */
/*                                                     ██   ██ ██████         */
/*   main.c                                            ██   ██      ██        */
/*                                                     ███████  █████         */
/*   By: maroy <maroy@student.42.qc>                        ██ ██             */
/*                                                          ██ ███████.qc     */
/*   Created: 2023/07/14 21:56:43 by maroy                                    */
/*   Updated: 2023/08/27 15:19:57 by maroy            >(.)__ <(.)__ =(.)__    */
/*                                                     (___/  (___/  (___/    */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	exec_stdin(t_minishell *minishell)
{
	int		fd[2];

	(void)minishell;
	if (pipe(fd) == -1)
	{
		print_msg_error("pipe error");
		return ;
	}
	fd[OUTFILE] = handle_file(TMP_FILE, O_RDWR | O_CREAT | O_TRUNC);
	close(fd[OUTFILE]);
	dup2(fd[INFILE], STDIN_FILENO);
	close(fd[INFILE]);
}



void	sanitize_arg(t_minishell *minishell)
{
	int i;
	int j;
	char **tmp;

	i = -1;
	j = 0;
	tmp = malloc(sizeof(char *) * (minishell->argc + 1));
	while (minishell->argv[++i])
	{
		if (ft_strncmp(minishell->argv[i], "<<" , 3) == 0)
			i += 2;
		if (minishell->argv)
			tmp[j++] = ft_strdup(minishell->argv[i]);
	}
	tmp[j] = NULL;
	if (j == 1 && ft_strncmp(tmp[0], "cat", 3) == 0)
	{
		tmp[++j] = ft_strdup("ayoo");
		tmp[--j] = NULL;
	}
	ft_free_tab(minishell->argv);
	minishell->argv = tmp;
	minishell->argc = j;
}


int8_t read_input(char *buffer, t_minishell *minishell)
{
	int i;

	if (handle_tokens(buffer, minishell))
		return (EXIT_FAILURE);
	i = -1;
	
	while (minishell->argv[++i])
	{
		if (ft_strncmp(minishell->argv[i], "<<", 3) == 0 && minishell->argv[i + 1])
		{
			exec_stdin(minishell);
			if (ft_strncmp(minishell->argv[0], "<<", 3) == 0 && minishell->argv[2] == NULL)
			{
				ft_free_tab(minishell->argv);
				minishell->argc = 0;
				return (EXIT_FAILURE);
			}
			sanitize_arg(minishell);
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
		DEBUG_print_tab(minishell->argv);
		status = handle_execute(minishell);
		ft_free_tab(minishell->argv);
	}
	destroy_program(minishell);
	write_history(HISTORY_FILE);
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
	read_history(HISTORY_FILE);
	master(envp);

	tcsetattr(STDIN_FILENO, TCSANOW, &term);
	return (EXIT_SUCCESS);
}
