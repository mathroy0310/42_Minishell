/* ************************************************************************** */
/*                                                                            */
/*                                                     ██   ██ ██████         */
/*   env.c                                             ██   ██      ██        */
/*                                                     ███████  █████         */
/*   By: maroy <maroy@student.42.qc>                        ██ ██             */
/*                                                          ██ ███████.qc     */
/*   Created: 2023/07/31 15:20:11 by maroy                                    */
/*   Updated: 2023/07/31 17:42:44 by maroy            >(.)__ <(.)__ =(.)__    */
/*                                                     (___/  (___/  (___/    */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int exec_env(t_env *env)
{
    while (env && env->next != NULL)
    {
        ft_putendl_fd(env->value, 1);
        env = env->next;
    }
    if (env)
        ft_putendl_fd(env->value, 1);
    return (EXIT_SUCCESS);
}
