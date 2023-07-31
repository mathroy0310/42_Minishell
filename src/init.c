/* ************************************************************************** */
/*                                                                            */
/*                                                     ██   ██ ██████         */
/*   init.c                                            ██   ██      ██        */
/*                                                     ███████  █████         */
/*   By: maroy <maroy@student.42.qc>                        ██ ██             */
/*                                                          ██ ███████.qc     */
/*   Created: 2023/07/31 17:43:00 by maroy                                    */
/*   Updated: 2023/07/31 17:56:24 by maroy            >(.)__ <(.)__ =(.)__    */
/*                                                     (___/  (___/  (___/    */
/* ************************************************************************** */

#include "../inc/minishell.h"


void init(t_minishell *minishell)
{
    minishell->exit_status = 0;
    minishell->cmd = NULL;
    minishell->cmd_list = NULL;
    minishell->pwd = NULL;
    minishell->oldpwd = NULL;
    
   init_env(minishell->env);
}