/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maroy <maroy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 13:25:54 by maroy             #+#    #+#             */
/*   Updated: 2023/08/29 19:41:38 by maroy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	is_child_process(int signum)
{
		if (signum == SIGQUIT)
			ft_putstr_fd("Quit: 3\n", 1);
		else if (signum == SIGINT)
			ft_putchar_fd('\n', 1);
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