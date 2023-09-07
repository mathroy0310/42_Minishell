/* ************************************************************************** */
/*                                                                            */
/*                                                     ██   ██ ██████         */
/*   builtins.c                                        ██   ██      ██        */
/*                                                     ███████  █████         */
/*   By: maroy <maroy@student.42.qc>                        ██ ██             */
/*                                                          ██ ███████.qc     */
/*   Created: 2023/07/31 16:21:04 by maroy                                    */
/*   Updated: 2023/09/07 13:11:30 by maroy            >(.)__ <(.)__ =(.)__    */
/*                                                     (___/  (___/  (___/    */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

uint8_t	check_builtin(t_cmd *cmd, t_data *data)
{
	char	**args;

	args = cmd->argvs;
	if (ft_strequal(args[0], "pwd"))
		return (pwd_builtin());
	else if (ft_strequal(args[0], "env"))
		return (env_builtin(data));
	else if (ft_strequal(args[0], "export"))
		return (export_builtin(args, data));
	// else if (ft_strequal(args[0], "echo"))
	// 	return (echo_builtin(args));
	// else if (ft_strequal(args[0], "unset"))
	// 	return (unset_builtin(args, data));
	// else if (ft_strequal(args[0], "cd"))
	// 	return (cd_builtin(args));
	// else if (ft_strequal(args[0], "exit"))
	// 	return (exit_builtin(args));
	return (KO);
}

uint8_t	is_builtin(t_cmd *cmd)
{
	char	**argvs;

	if (!cmd->argvs)
		return (KO);
	argvs = cmd->argvs;
	if ((ft_strequal(argvs[0], "echo")) || (ft_strequal(argvs[0], "cd"))
		|| (ft_strequal(argvs[0], "pwd")) || (ft_strequal(argvs[0], "export"))
		|| (ft_strequal(argvs[0], "unset")) || (ft_strequal(argvs[0], "env"))
		|| (ft_strequal(argvs[0], "exit")))
		return (OK);
	else
		return (KO);
}
