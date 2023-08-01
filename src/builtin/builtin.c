/* ************************************************************************** */
/*                                                                            */
/*                                                     ██   ██ ██████         */
/*   builtin.c                                         ██   ██      ██        */
/*                                                     ███████  █████         */
/*   By: maroy <maroy@student.42.qc>                        ██ ██             */
/*                                                          ██ ███████.qc     */
/*   Created: 2023/07/31 16:21:04 by maroy                                    */
/*   Updated: 2023/08/01 12:52:59 by maroy            >(.)__ <(.)__ =(.)__    */
/*                                                     (___/  (___/  (___/    */
/* ************************************************************************** */

#include "../../inc/minishell.h"
typedef enum e_builtin
{
    ENV,
    EXPORT,
    UNSET,
    CD,
    PWD,
    EXIT
}			t_builtin;

static int8_t is_builtin(char * cmd)
{
	if (ft_strcmp(cmd, "env") == 0)
		return (ENV);
	else if (ft_strcmp(cmd, "export") == 0)
		return (EXPORT);
	else if (ft_strcmp(cmd, "unset") == 0)
		return (UNSET);
	else if (ft_strcmp(cmd, "cd") == 0)
		return (CD);
	else if (ft_strcmp(cmd, "pwd") == 0)
		return (PWD);
	else if (ft_strcmp(cmd, "exit") == 0)
		return (EXIT);
	return (NONE);
}

//TODO -- fonction pour chaque builtin
static int8_t	exec_builtin(t_minishell *minishell, int builtin_type)
{
	int result;

	result = 0;

	if (builtin_type == ENV)
		result = exec_env(minishell->env);
	else if (builtin_type == EXPORT)
		result = exec_export(minishell);
	else if (builtin_type == UNSET)
		result = exec_unset(minishell);
	else if (builtin_type == CD)
		result = exec_cd(minishell);
	else if (builtin_type == PWD)
		result = exec_pwd();
	else if (builtin_type == EXIT)
		result = exec_exit(minishell);
	return (result);
}

int8_t	exec_cmd(t_minishell *minishell)
{
	int8_t builtin_type;
	
	builtin_type = is_builtin(minishell->cmd);
	if (builtin_type == NONE)
		return (exec_builtin(minishell, builtin_type));
	else
		return (exec_bin());
	return (0);
}