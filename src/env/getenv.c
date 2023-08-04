/* ************************************************************************** */
/*                                                                            */
/*                                                     ██   ██ ██████         */
/*   getenv.c                                          ██   ██      ██        */
/*                                                     ███████  █████         */
/*   By: maroy <maroy@student.42.qc>                        ██ ██             */
/*                                                          ██ ███████.qc     */
/*   Created: 2023/07/31 16:14:52 by maroy                                    */
/*   Updated: 2023/08/04 13:33:18 by maroy            >(.)__ <(.)__ =(.)__    */
/*                                                     (___/  (___/  (___/    */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void init_env(t_minishell *minishell, char **envp )
{
    t_env *env;
    t_env *tmp;
    int i;
    
    env = ft_malloc(sizeof(t_env));
    env->value = ft_strdup(envp[0]);
    env->next = NULL;
    minishell->env = env;
    i = 1;
    while (envp && envp[0] && envp[i])
    {
        tmp = ft_malloc(sizeof(t_env));
        tmp->value = ft_strdup(envp[i]);
        tmp->next = NULL;
        env->next = tmp;
        env = tmp;
        i++;
    }
}