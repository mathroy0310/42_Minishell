/* ************************************************************************** */
/*                                                                            */
/*                                                     ██   ██ ██████         */
/*   signal.c                                          ██   ██      ██        */
/*                                                     ███████  █████         */
/*   By: maroy <maroy@student.42.qc>                        ██ ██             */
/*                                                          ██ ███████.qc     */
/*   Created: 2023/08/01 13:25:54 by maroy                                    */
/*   Updated: 2023/08/01 14:10:17 by maroy            >(.)__ <(.)__ =(.)__    */
/*                                                     (___/  (___/  (___/    */
/* ************************************************************************** */

# include "../inc/minishell.h"

static void	signal_handler(int sig)
{
	if (sig == SIGINT)
		printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	set_signal(void)
{
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, signal_handler);
}