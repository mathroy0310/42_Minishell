/* ************************************************************************** */
/*                                                                            */
/*                                                     ██   ██ ██████         */
/*   pwd.c                                             ██   ██      ██        */
/*                                                     ███████  █████         */
/*   By: maroy <maroy@student.42.qc>                        ██ ██             */
/*                                                          ██ ███████.qc     */
/*   Created: 2023/07/31 15:20:18 by maroy                                    */
/*   Updated: 2023/08/01 12:40:25 by maroy            >(.)__ <(.)__ =(.)__    */
/*                                                     (___/  (___/  (___/    */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int8_t exec_pwd(void)
{
    char cwd[PATH_MAX];

    if (getcwd(cwd, PATH_MAX))
    {
        ft_putendl_fd(cwd, 1);
        return (EXIT_SUCCESS);
    }
    return (EXIT_FAILURE);
}