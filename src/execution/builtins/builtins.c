/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maroy <maroy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 16:21:04 by maroy             #+#    #+#             */
/*   Updated: 2024/01/02 00:15:36 by maroy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_u8	execute_builtin(t_cmd *cmd, t_data *data)
{
	char	**args;

	args = cmd->argvs;
	if (ft_strequal(args[0], "pwd"))
		return (pwd_builtin());
	else if (ft_strequal(args[0], "env"))
		return (env_builtin(data));
	else if (ft_strequal(args[0], "export"))
		return (export_builtin(args, data));
	else if (ft_strequal(args[0], "unset"))
		return (unset_builtin(args, data));
	else if (ft_strequal(args[0], "echo"))
		return (echo_builtin(args));
	else if (ft_strequal(args[0], "cd"))
		return (cd_builtin(args));
	return (KO);
}

void	is_builtin(t_cmd *cmd, t_data *data)
{
	if (!cmd->argvs)
		return ;
	if (ft_strequal(cmd->argvs[0], "echo")
		|| ft_strequal(cmd->argvs[0], "cd")
		|| ft_strequal(cmd->argvs[0], "pwd")
		|| ft_strequal(cmd->argvs[0], "export")
		|| ft_strequal(cmd->argvs[0], "unset")
		|| ft_strequal(cmd->argvs[0], "env"))
		data->is_builtin = TRUE;
	return ;
}
