/* ************************************************************************** */
/*                                                                            */
/*                                                     ██   ██ ██████         */
/*   signals.c                                         ██   ██      ██        */
/*                                                     ███████  █████         */
/*   By: maroy <maroy@student.42.qc>                        ██ ██             */
/*                                                          ██ ███████.qc     */
/*   Created: 2023/08/01 13:25:54 by maroy                                    */
/*   Updated: 2023/10/04 17:54:47 by maroy            >(.)__ <(.)__ =(.)__    */
/*                                                     (___/  (___/  (___/    */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	is_child_process(int signum)
{
	if (signum == SIGQUIT)
		ft_putendl_fd("Quit: 3", STDOUT_FILENO);
	else if (signum == SIGINT)
		ft_putchar_fd('\n', STDOUT_FILENO);
}

void	sigint_handler(int signum)
{
	if (g_global->pid == 0)
		is_child_process(signum);
	else
	{
		if (signum == SIGINT)
		{
			g_global->exit_status = EXIT_FAILURE;
			ft_putchar_fd('\n', STDOUT_FILENO);
			rl_replace_line("", 0);
			rl_on_new_line();
			rl_redisplay();
		}
		else if (signum == SIGQUIT)
		{
			rl_on_new_line();
			rl_redisplay();
		}
	}
}
