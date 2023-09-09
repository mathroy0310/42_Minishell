/* ************************************************************************** */
/*                                                                            */
/*                                                     ██   ██ ██████         */
/*   unset.c                                           ██   ██      ██        */
/*                                                     ███████  █████         */
/*   By: maroy <maroy@student.42.qc>                        ██ ██             */
/*                                                          ██ ███████.qc     */
/*   Created: 2023/09/08 14:05:13 by maroy                                    */
/*   Updated: 2023/09/09 19:19:14 by maroy            >(.)__ <(.)__ =(.)__    */
/*                                                     (___/  (___/  (___/    */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

uint8_t	unset_builtin(char **args, t_data *data)
{
	int	i;

	i = 0;
	g_global->exit_status = 0;


	(void)args;
	(void)data;
	return (OK);
}
