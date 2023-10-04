/* ************************************************************************** */
/*                                                                            */
/*                                                     ██   ██ ██████         */
/*   exec_multi_cmd_utils.c                            ██   ██      ██        */
/*                                                     ███████  █████         */
/*   By: maroy <maroy@student.42.qc>                        ██ ██             */
/*                                                          ██ ███████.qc     */
/*   Created: 2023/08/30 18:12:50 by maroy                                    */
/*   Updated: 2023/10/04 18:01:09 by maroy            >(.)__ <(.)__ =(.)__    */
/*                                                     (___/  (___/  (___/    */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	setup_input(t_cmd *cmd, t_data *data, int j)
{
	int	fd;

	fd = open(cmd->redir[j].filename, O_RDWR);
	if (fd < 0)
	{
		print_error(cmd->redir[j].filename);
		data->redir->is_error = true;
		return ;
	}
	else
		data->redir->infile = fd;
}

void	setup_output(t_cmd *cmd, t_data *data, int j)
{
	int	fd;

	fd = 0;
	if (cmd->redir[j].type == great)
	{
		fd = open(cmd->redir[j].filename, O_RDWR | O_CREAT | O_TRUNC, S_IRWXU);
		if (fd < 0)
		{
			data->redir->is_error = true;
			print_error(cmd->redir[j].filename);
		}
	}
	else if (cmd->redir[j].type == greater)
	{
		fd = open(cmd->redir[j].filename, O_RDWR | O_CREAT | O_APPEND, S_IRWXU);
		if (fd < 0)
		{
			data->redir->is_error = true;
			print_error(cmd->redir[j].filename);
			}
	}
	data->redir->outfile = fd;
}
