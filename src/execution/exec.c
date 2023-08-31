/* ************************************************************************** */
/*                                                                            */
/*                                                     ██   ██ ██████         */
/*   exec.c                                            ██   ██      ██        */
/*                                                     ███████  █████         */
/*   By: maroy <maroy@student.42.qc>                        ██ ██             */
/*                                                          ██ ███████.qc     */
/*   Created: 2023/08/30 18:12:50 by maroy                                    */
/*   Updated: 2023/08/30 19:17:27 by maroy            >(.)__ <(.)__ =(.)__    */
/*                                                     (___/  (___/  (___/    */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	init_data(t_data *data, t_state *state)
{
	g_global->pid = 1;
	if (state->path != NULL)
		ft_free_tab(state->path);
	//state->path = get_path();
	data->saved_stdout = dup(0);
	data->saved_stdin = dup(1);
	data->state = state;
	data->redir = (t_shell_red *)malloc(sizeof(t_shell_red));
	data->redir->infile = 0;
	data->redir->outfile = 0;
	data->redir->here_doc = 0;
	data->redir->error = 0;
}

uint8_t	is_builtin(t_cmd *cmd)
{
	char	**argvs;

	if (!cmd->argvs)
		return (KO);
	argvs = cmd->argvs;
	if ((ft_strequal(argvs[0], "echo")) || (ft_strequal(argvs[0], "cd")) ||
		(ft_strequal(argvs[0], "pwd")) || (ft_strequal(argvs[0], "export")) ||
		(ft_strequal(argvs[0], "unset")) || (ft_strequal(argvs[0], "env")) ||
		(ft_strequal(argvs[0], "exit")))
		return (OK);
	else
		return (KO);
}

int	execute_cmd(t_cmd *cmd, t_data *data)
{
	(void)data;
	if (is_builtin(cmd))
	{
		DEBUG_print_msg("is_builtin == true");
		return (OK);
	}
	return (OK);
}

void	execution(t_cmd *cmd, t_state *state)
{
	t_data *data;

	data = (t_data *)malloc(sizeof(t_data));
	if (cmd->redir_nbr == 0 && cmd->type == eof)
	{
		init_data(data, state);
		execute_cmd(cmd, data);
	}
}