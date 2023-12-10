/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maroy <maroy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 18:12:50 by maroy             #+#    #+#             */
/*   Updated: 2023/12/09 19:48:32 by maroy            ###   ########.fr       */
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

static char	**get_path(void)
{
	char	**path;
	char	*tmp;
	int		ret;

	ret = find_env_var_index("PATH", g_global->env_var);
	if (ret == -1)
		return (NULL);
	tmp = return_value(g_global->env_var[ret], '=');
	path = ft_split(tmp, ':');
	if (path[0] == NULL)
		return (NULL);
	if (!path)
		return (NULL);
	return (path);
}

void	init_data(t_data *data, t_state *state)
{
	if (state->path != NULL)
		ft_free_tab(state->path);
	state->path = get_path();
	data->saved_stdout_fd = dup(STDOUT_FILENO);
	data->saved_stdin_fd = dup(STDIN_FILENO);
	data->state = state;
	data->redir = (t_shell_red *)ft_malloc(sizeof(t_shell_red));
	data->redir->filename = NULL;
	data->redir->infile = 0;
	data->redir->outfile = 0;
	data->redir->is_here_doc = FALSE;
	data->redir->pipe_fd = NULL;
	data->redir->is_error = FALSE;
	g_global->exit_status = EXIT_SUCCESS;
}

t_u8	execution(t_cmd *cmd, t_state *state)
{
	t_data	*data;

	data = (t_data *)malloc(sizeof(t_data) * cmd->nbr_cmd);
	init_data(data, state);
	if (ft_strequal(cmd->argvs[0], "exit"))
		exit_builtin(cmd->argvs);
	else if (cmd->nbr_cmd == 0)
		return (OK);
	else if (cmd->type == pip)
		execute_multi_cmd(cmd, data);
	else
	{
		if (cmd->redir_nbr > 0)
			// check here doc
			execute_simple_cmd(cmd, data);
		else
			execute_regular_cmd(cmd, data);
		// ft_debug_printf("no redirection");
	}
	signals_init();
	free_data(data, cmd);
	return (OK);
}
