/* ************************************************************************** */
/*                                                                            */
/*                                                     ██   ██ ██████         */
/*   init.c                                            ██   ██      ██        */
/*                                                     ███████  █████         */
/*   By: maroy <maroy@student.42.qc>                        ██ ██             */
/*                                                          ██ ███████.qc     */
/*   Created: 2023/07/31 17:43:00 by maroy                                    */
/*   Updated: 2023/08/04 13:33:55 by maroy            >(.)__ <(.)__ =(.)__    */
/*                                                     (___/  (___/  (___/    */
/* ************************************************************************** */

#include "../inc/minishell.h"


int8_t init(t_minishell *minishell, char **envp)
{
	struct termios	term;

	set_signal();
	init_env(minishell, envp);
	if (tcgetattr(STDIN_FILENO, &term) == -1)
		return (0);
	//MACOS term.c_lflag &= ~(ECHOCTL);
	term.c_lflag &= ~(ECHONL);
	if (tcsetattr(STDIN_FILENO, TCSANOW, &term) == -1)
		return(0);

	minishell->exit_status = 0;
	minishell->cmd = NULL;
	minishell->pwd = NULL;
	minishell->oldpwd = NULL;
	
	minishell->fd_in = dup(STDIN_FILENO);
	minishell->fd_out = dup(STDOUT_FILENO);
	return(EXIT_SUCCESS);
}