/* ************************************************************************** */
/*                                                                            */
/*                                                     ██   ██ ██████         */
/*   pwd.c                                             ██   ██      ██        */
/*                                                     ███████  █████         */
/*   By: maroy <maroy@student.42.qc>                        ██ ██             */
/*                                                          ██ ███████.qc     */
/*   Created: 2023/07/31 15:20:18 by maroy                                    */
/*   Updated: 2023/10/04 17:21:46 by maroy            >(.)__ <(.)__ =(.)__    */
/*                                                     (___/  (___/  (___/    */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

uint8_t	pwd_builtin(void)
{
	char	cwd[PATH_MAX];

	g_global->exit_status = EXIT_SUCCESS;
	if (getcwd(cwd, PATH_MAX))
	{
		ft_putendl_fd(cwd, STDOUT_FILENO);
		return (EXIT_SUCCESS);
	}
	ft_putendl_fd(get_env_var_by_key("PWD"), STDOUT_FILENO);
	return (EXIT_FAILURE);
}
