/* ************************************************************************** */
/*                                                                            */
/*                                                     ██   ██ ██████         */
/*   execution.c                                       ██   ██      ██        */
/*                                                     ███████  █████         */
/*   By: maroy <maroy@student.42.qc>                        ██ ██             */
/*                                                          ██ ███████.qc     */
/*   Created: 2023/07/14 21:56:43 by maroy                                    */
/*   Updated: 2023/07/31 15:40:35 by maroy            >(.)__ <(.)__ =(.)__    */
/*                                                     (___/  (___/  (___/    */
/* ************************************************************************** */

#include "../../inc/minishell.h"


int handle_execution(t_minishell *minishell
{
    int fds[4];
    int pipe_stdin;
    int i;

    pipe_stdin = dup(STDIN_FILENO);
    i = 0;
    pipe(fds);
    pipe(fds + 2);
}


// static int is_builtin(char * cmd)
// {
// 	if (ft_strcmp(cmd, "env") == 0)
// 		return (ENV);
// 	else if (ft_strcmp(cmd, "export") == 0)
// 		return (EXPORT);
// 	else if (ft_strcmp(cmd, "unset") == 0)
// 		return (UNSET);
// 	else if (ft_strcmp(cmd, "cd") == 0)
// 		return (CD);
// 	else if (ft_strcmp(cmd, "pwd") == 0)
// 		return (PWD);
// 	else if (ft_strcmp(cmd, "exit") == 0)
// 		return (EXIT);
// 	return (-1);
// }

// //TODO -- fonction pour chaque builtin
// static int	exec_builtin(t_minishell *minishell, int builtin_type)
// {
// 	int result;

// 	result = 0;

// 	if (builtin_type == ENV)
// 		result = exec_env(minishell->env);
// 	else if (builtin_type == EXPORT)
// 		result = exec_export(minishell);
// 	else if (builtin_type == UNSET)
// 		result = exec_unset(minishell);
// 	else if (builtin_type == CD)
// 		result = exec_cd(minishell);
// 	else if (builtin_type == PWD)
// 		result = exec_pwd();
// 	else if (builtin_type == EXIT)
// 		result = exec_exit(minishell);
// 	return (result);
// }

// int	exec_cmd(t_minishell *minishell)
// {
// 	int builtin_type;
	
// 	builtin_type = is_builtin(minishell->cmd);
// 	if (builtin_type > 0)
// 		return (exec_builtin(minishell, builtin_type));
// 	else
// 		return (exec_bin());
// 	return (0);
// }
