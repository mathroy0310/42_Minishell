/* ************************************************************************** */
/*                                                                            */
/*                                                     ██   ██ ██████         */
/*   signal.c                                          ██   ██      ██        */
/*                                                     ███████  █████         */
/*   By: maroy <maroy@student.42.qc>                        ██ ██             */
/*                                                          ██ ███████.qc     */
/*   Created: 2023/08/01 13:25:54 by maroy                                    */
/*   Updated: 2023/08/03 11:48:52 by maroy            >(.)__ <(.)__ =(.)__    */
/*                                                     (___/  (___/  (___/    */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	*get_signal_triggered_status(void)
{
	static int	*triggered;

	if (!triggered)
	{
		triggered = (int *)malloc(sizeof(int));
		*triggered = 0;
	}
	return (triggered);
}

void	sig_interrupt(int sig)
{
	if (sig == SIGINT)
	{
		ft_putstr_fd("\n", STDERR_FILENO);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	handle_heredoc_signal(int signal_number)
{
	int	*triggered;

	triggered = get_signal_triggered_status();
	if (signal_number == SIGINT)
	{
		*triggered = 1;
		signal(SIGINT, handle_heredoc_signal);
	}
}