/* ************************************************************************** */
/*                                                                            */
/*                                                     ██   ██ ██████         */
/*   init.c                                            ██   ██      ██        */
/*                                                     ███████  █████         */
/*   By: maroy <maroy@student.42.qc>                        ██ ██             */
/*                                                          ██ ███████.qc     */
/*   Created: 2023/07/31 17:43:00 by maroy                                    */
/*   Updated: 2023/08/01 15:02:25 by maroy            >(.)__ <(.)__ =(.)__    */
/*                                                     (___/  (___/  (___/    */
/* ************************************************************************** */

#include "../inc/minishell.h"


int8_t init(t_minishell *minishell)
{
	struct termios	term;

	set_signal();
	if (tcgetattr(STDIN_FILENO, &term) == -1)
		return (KO);
	term.c_lflag &= ~(ECHOCTL);
	if (tcsetattr(STDIN_FILENO, TCSANOW, &term) == -1)
		return(KO);

	minishell->exit_status = 0;
	minishell->cmd = NULL;
	minishell->pwd = NULL;
	minishell->oldpwd = NULL;
	
	init_env(minishell->env);
	return(EXIT_SUCCESS);
}