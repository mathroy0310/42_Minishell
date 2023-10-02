/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maroy <maroy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 18:12:50 by maroy             #+#    #+#             */
/*   Updated: 2023/10/02 15:59:00 by maroy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"
#include "../../inc/builtins.h"

void	wait_children(void)
{
	int		status;
	int		signal;

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

uint8_t	dup_env_var(char **env)
{
	int	i;

	i = -1;
	g_global->env_var = (char **)malloc(sizeof(char *) * (ft_tablen(env) + 1));
	if (g_global->env_var == NULL)
		exit(EXIT_FAILURE);
	while (++i < ft_tablen(env))
		g_global->env_var[i] = ft_strdup(env[i]);
	g_global->env_var[i] = 0;
	return (OK);
}

char	**get_path(void)
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
	g_global->pid = 1;
	if (state->path != NULL)
		ft_free_tab(state->path);
	state->path = get_path();
	data->saved_stdout = dup(0);
	data->saved_stdin = dup(1);
	data->state = state;
	data->redir = (t_shell_red *)malloc(sizeof(t_shell_red));
	data->redir->infile = 0;
	data->redir->outfile = 0;
	data->redir->here_doc = 0;
	data->redir->filename = NULL;
	data->redir->pipe_fd = NULL;
	data->redir->is_error = false;
}

void	restore_std(int saved_stdout, int saved_stdin)
{
	dup2(saved_stdout, STDOUT_FILENO);
	dup2(saved_stdin, STDIN_FILENO);
	close(saved_stdout);
	close(saved_stdin);
}

uint8_t	execution(t_cmd *cmd, t_state *state)
{
	t_data	*data;

	data = (t_data *)malloc(sizeof(t_data) * cmd->nbr_cmd);
	if (cmd->redir_nbr == 0 && cmd->type == eof)
	{
		init_data(data, state);
		execute_reg_cmd(cmd, data);
	}
	else if (cmd->redir_nbr > 0 && cmd->type == eof)
	{
		init_data(data, state);
		check_for_heredoc(data, cmd);
		execute_single_cmd(cmd, data);
	}
	else
		execute_multi_cmd(cmd, data, state);
	main_free(data, cmd);
	return (OK);
}
