/* ************************************************************************** */
/*                                                                            */
/*                                                     ██   ██ ██████         */
/*   exec_reg_cmd.c                                    ██   ██      ██        */
/*                                                     ███████  █████         */
/*   By: maroy <maroy@student.42.qc>                        ██ ██             */
/*                                                          ██ ███████.qc     */
/*   Created: 2023/09/13 15:58:19 by maroy                                    */
/*   Updated: 2023/10/28 16:47:35 by maroy            >(.)__ <(.)__ =(.)__    */
/*                                                     (___/  (___/  (___/    */
/* ************************************************************************** */

#include "minishell.h"

void	check_for_errors(t_cmd *cmd, t_data *data)
{
	if (!cmd->argvs)
		exit(g_global->exit_status);
	if (data->redir->is_error)
	{
		g_global->exit_status = EXIT_FAILURE;
		exit(g_global->exit_status);
	}
	if (!ft_strcmp(cmd->argvs[0], "\0"))
	{
		ft_putstr_err(ANSI_COLOR_BRIGHT_RED ERR_PROMPT);
		ft_putstr_err(": command not found");
		ft_putstr_errnl(ANSI_COLOR_RESET);
		exit(g_global->exit_status);
	}
	/// FAUT CHANGER CA LOL !!!! ya no way quon garde ca de meme
	if ((!ft_strcmp(cmd->argvs[0], "./")) || (!ft_strcmp(cmd->argvs[0], "../")))
	{
		ft_putstr_err(ANSI_COLOR_BRIGHT_RED ERR_PROMPT);
		ft_putstr_err(cmd->argvs[0]);
		ft_putstr_err(": is a directory");
		ft_putstr_errnl(ANSI_COLOR_RESET);
		exit(g_global->exit_status);
	}
	if (!ft_strcmp(cmd->argvs[0], "."))
	{
		ft_putstr_err(ANSI_COLOR_BRIGHT_RED ERR_PROMPT);
		ft_putstr_err("filename argument required");
		ft_putstr_err(".: usage: . filename [arguments]");
		ft_putstr_errnl(ANSI_COLOR_RESET);
		exit(g_global->exit_status);
	}
}

static t_u8	check_for_permission(t_cmd *cmd)
{
	/// ici a place pour le `.` et `./`
	/// ca veut dire quil reussi a execve `.` ou `./`
	if (access(cmd->argvs[0], F_OK | X_OK) != 0)
	{
		ft_putstr_err(ANSI_COLOR_BRIGHT_RED ERR_PROMPT);
		ft_putstr_err(cmd->argvs[0]);
		ft_putstr_err(": Permission denied");
		ft_putstr_errnl(ANSI_COLOR_RESET);
		return (126);
	}
	return (OK);
}

void	find_cmd_path(t_cmd *cmd, t_data *data)
{
	char	*possible_path;
	int		fd;

	check_for_errors(cmd, data);
	possible_path = find_path(cmd->argvs[0], data->state->path);
	if (possible_path == NULL)
		possible_path = ft_strdup(cmd->argvs[0]);
	fd = open(possible_path, O_RDONLY);
	if (fd < 0)
	{
		if (!path_error_print(cmd, data, possible_path))
		{
			free(possible_path);
			exit(g_global->exit_status);
		}
	}
	if (execve(possible_path, cmd->argvs, g_global->env_var))
		exit(check_for_permission(cmd));
}

t_u8	execute_reg_cmd(t_cmd *cmd, t_data *data)
{
	pid_t	child_pid;

	if (is_builtin(cmd))
	{
		debug_print_msg("is_builtin == true");
		return (check_builtin(cmd, data));
	}
	else
	{
		g_global->pid = 0;
		child_pid = fork();
		if (child_pid < 0)
			fork_failed();
		else if (child_pid == 0)
			find_cmd_path(cmd, data);
		wait_children();
		g_global->pid = 1;
		restore_std(data->saved_stdout, data->saved_stdin);
	}
	return (OK);
}
