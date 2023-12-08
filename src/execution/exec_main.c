/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maroy <maroy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 18:12:50 by maroy             #+#    #+#             */
/*   Updated: 2023/12/08 16:55:09 by maroy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_bool	is_valid_envar(char c)
{
	if (ft_isalnum(c) || c == '_' || c == '~')
		return (true);
	return (false);
}

t_u8	dup_env_var(char **env)
{
	int	i;

	i = -1;
	g_global->env_var = (char **)ft_malloc(sizeof(char *) * (ft_tablen(env)
				+ 1));
	while (++i < ft_tablen(env))
		g_global->env_var[i] = ft_strdup(env[i]);
	g_global->env_var[i] = NULL;
	return (OK);
}

void	init_data(t_data *data, t_state *state)
{
	(void)state;
	(void)data;
	// state->path = get_path();
	data = (t_data *)ft_malloc(sizeof(t_data));
	data->saved_stdout_fd = STDOUT_FILENO;
	data->saved_stdin_fd = STDIN_FILENO;
	data->state = state;
	data->redir = (t_shell_red *)ft_malloc(sizeof(t_shell_red));
	data->redir->filename = NULL;
	data->redir->infile = NULL;
	data->redir->outfile = NULL;
	data->redir->is_here_doc = FALSE;
	data->redir->pipe_fd = NULL;
	data->redir->is_error = FALSE;
}

t_u8	execution(t_cmd *cmd, t_state *state)
{
	t_data	*data;

	data = NULL;
	if (cmd->nbr_cmd == 0)
		return (OK);
	if (cmd->type == pip)
		return (execute_multi_cmd(cmd, data));
	else
	{
		init_data(data, state);
		if (cmd->redir_nbr > 0)
			// check here doc
			execute_simple_cmd(cmd, data);
		else
			execute_regular_cmd(cmd, data);
		// ft_debug_printf("no redirection");
	}
	//free_data(data, cmd);
	return (OK);
}
