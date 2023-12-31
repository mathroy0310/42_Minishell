/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maroy <maroy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 13:25:54 by maroy             #+#    #+#             */
/*   Updated: 2023/11/28 21:16:28 by maroy            ###   ########.fr       */
/*                                                                            */
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
	(void)signum;
	g_global->exit_status = EXIT_FAILURE;
	ft_putchar('\n');
	rl_replace_line("", 0);
	rl_on_new_line();
	exit(g_global->exit_status);
}

void	is_child_process(int signum)
{
		if (signum == SIGQUIT)
			ft_putstr_nl("Quit");
		else if (signum == SIGINT)
			ft_putchar('\n');
}

void	sigint_handler(int signum)
{
	if (g_global->pid == 0)
		is_child_process(signum);
	else
	{
		if (signum == SIGINT)
		{
			
			g_global->exit_status = 1;
			ft_putchar_fd('\n', 2);
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

void	signals_init(void)
{
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, sigint_handler);
}
