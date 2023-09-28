/* ************************************************************************** */
/*                                                                            */
/*                                                     ██   ██ ██████         */
/*   exec_multi_cmd.c                                  ██   ██      ██        */
/*                                                     ███████  █████         */
/*   By: maroy <maroy@student.42.qc>                        ██ ██             */
/*                                                          ██ ███████.qc     */
/*   Created: 2023/09/23 14:48:08 by maroy                                    */
/*   Updated: 2023/09/28 15:06:31 by maroy            >(.)__ <(.)__ =(.)__    */
/*                                                     (___/  (___/  (___/    */
/* ************************************************************************** */

#include "../../inc/minishell.h"
#include "stdbool.h"

void	pipe_all(t_cmd *cmd, t_data *data, t_state *state)
{
	int	i;

	i = -1;
	while (++i < cmd->nbr_cmd - 1)
	{

	}

}


void	execute_multi_cmd(t_cmd *cmd, t_data *data, t_state *state)
{
	int		i;
	bool	is_redir;

	(void)cmd;
	(void)data;
	i = -1;
	is_redir = false;
	while (++i < cmd->nbr_cmd)
		if (cmd[i].redir_nbr != 0)
			is_redir = true;
	if (!is_redir)
	{
		execute_simple_pipe(cmd, data, state);
		return ;
	}
	else
	{
		execute_pipe_redir(cmd, data, state);
	}
	g_global->pid = 0;
}
