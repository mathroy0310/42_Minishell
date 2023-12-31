/* ************************************************************************** */
/*                                                                            */
/*                                                     ██   ██ ██████         */
/*   pwd.c                                             ██   ██      ██        */
/*                                                     ███████  █████         */
/*   By: maroy <maroy@student.42.qc>                        ██ ██             */
/*                                                          ██ ███████.qc     */
/*   Created: 2023/07/31 15:20:18 by maroy                                    */
/*   Updated: 2023/10/28 16:44:04 by maroy            >(.)__ <(.)__ =(.)__    */
/*                                                     (___/  (___/  (___/    */
/* ************************************************************************** */

#include "minishell.h"

t_u8	pwd_builtin(void)
{
	char	cwd[PATH_MAX];

	g_global->exit_status = EXIT_SUCCESS;
	if (getcwd(cwd, PATH_MAX))
	{
		ft_putstr_nl(cwd);
		return (EXIT_SUCCESS);
	}
	ft_putstr_nl(get_env_var_by_key("PWD"));
	return (EXIT_FAILURE);
}
