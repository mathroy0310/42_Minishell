/* ************************************************************************** */
/*                                                                            */
/*                                                     ██   ██ ██████         */
/*   signals.c                                         ██   ██      ██        */
/*                                                     ███████  █████         */
/*   By: maroy <maroy@student.42.qc>                        ██ ██             */
/*                                                          ██ ███████.qc     */
/*   Created: 2023/08/01 13:25:54 by maroy                                    */
/*   Updated: 2023/11/08 14:57:07 by maroy            >(.)__ <(.)__ =(.)__    */
/*                                                     (___/  (___/  (___/    */
/* ************************************************************************** */

#include "minishell.h"

void	wait_children(void)
{
	int	status;
	int	signal;

	while (waitpid(-1, &status, 0) > 0)
	{
		if (WIFEXITED(status))
			g_global->exit_status = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
		{
			signal = WTERMSIG(status);
			g_global->exit_status = signal + 128;
		}
	}
}

void	sigint_here_doc_handler(int signum)
{
	if (signum == SIGINT)
	{
		g_global->exit_status = EXIT_FAILURE;
		ft_putchar('\n');
		rl_replace_line("", 0);
		rl_on_new_line();
		exit(g_global->exit_status);
	}
}

void	sigint_handler(int signum)
{
	if (g_global->pid == 0)
		return ;
	if (signum == SIGINT)
	{
		g_global->exit_status = EXIT_FAILURE;
		ft_putchar('\n');
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}

void	signals_init(void)
{
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);
}
