/* ************************************************************************** */
/*                                                                            */
/*                                                     ██   ██ ██████         */
/*   execution.c                                       ██   ██      ██        */
/*                                                     ███████  █████         */
/*   By: maroy <maroy@student.42.qc>                        ██ ██             */
/*                                                          ██ ███████.qc     */
/*   Created: 2023/07/14 21:56:43 by maroy                                    */
/*   Updated: 2023/08/15 16:15:39 by maroy            >(.)__ <(.)__ =(.)__    */
/*                                                     (___/  (___/  (___/    */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	handle_execute(t_minishell *minishell)
{
	int		fds[4];
	int		pipe_stdin;
	int		son_count;
	int		i;

	pipe_stdin = dup(STDIN_FILENO);
	i = 0;
	while (minishell->argv[i] && (ft_strncmp(minishell->argv[i], "|", 2) != 0))
		i++;
	pipe(fds);
	pipe(fds + 2);
    son_count = 0;
	//son_count = handle_pipes(fds, minishell);
	while (son_count-- > 0)
		wait(&minishell->exit_status);
	i = -1;
	while (++i < 4)
		close(fds[i]);
	dup2(pipe_stdin, STDIN_FILENO);
	minishell->exit_status = minishell->exit_status % 256;
	return (1);
}