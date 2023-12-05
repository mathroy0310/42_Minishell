/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maroy <maroy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 18:12:50 by maroy             #+#    #+#             */
/*   Updated: 2023/12/05 11:28:12 by maroy            ###   ########.fr       */
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

t_bool	is_valid_cmd(t_cmd *cmd)
{
	if (!cmd->argvs[0] && (cmd->args_size == 0 || cmd->args_size == 1))
		return (FALSE);
	return (FALSE);
}

t_u8	execution(t_cmd *cmd, t_state *state)
{
	(void)state;
	if (is_valid_cmd(cmd) == FALSE)
		return (g_global->exit_status);
	return (OK);
}
