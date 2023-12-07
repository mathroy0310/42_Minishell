/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maroy <maroy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 18:12:50 by maroy             #+#    #+#             */
/*   Updated: 2023/12/07 17:02:21 by maroy            ###   ########.fr       */
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
	g_global->env_var = (char **)malloc(sizeof(char *) * (ft_tablen(env) + 1));
	if (g_global->env_var == NULL)
		exit(EXIT_FAILURE);
	while (++i < ft_tablen(env))
		g_global->env_var[i] = ft_strdup(env[i]);
	g_global->env_var[i] = NULL;
	return (OK);
}

void init_data(t_data *data, t_state *state)
{
	(void)state;
	(void)data;

	//state->path = get_path();
// 	data = (t_data *)ft_malloc(sizeof(t_data));
// 	data->saved_stdout->c_fd = dup(STDOUT_FILENO);
// 	data->saved_stdin->c_fd = dup(STDIN_FILENO);
// 	data->state = state;
	
// 	data->redir = (t_shell_red *)ft_malloc(sizeof(t_shell_red));
// 	data->redir->infile = NULL;
// 	data->redir->outfile = NULL;
// 	data->redir->is_here_doc = FALSE;
// 	data->redir->filename = NULL;
// 	data->redir->pipe_fd = NULL;
// 	data->redir->is_error = FALSE;
}

t_u8	execution(t_cmd *cmd, t_state *state)
{
	(void)cmd;
	(void)state;
	t_data *data;
	t_file *file;

	data = NULL;
	
	init_data(data, state);
	if (cmd[0].redir_nbr > 0)
	{
		if (ft_is_file_exists(cmd[0].redir[0].filename))
		{
			ft_debug_printf	("file exists");
			file = ft_open_file(cmd[0].redir[0].filename, O_RDONLY);
			debug_print_file_info(file);
			ft_close_file(file);
		}
		else
			ft_debug_printf	("file doesn't exists");
	}
	
	
	return (OK);
}
