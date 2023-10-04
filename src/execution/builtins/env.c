/* ************************************************************************** */
/*                                                                            */
/*                                                     ██   ██ ██████         */
/*   env.c                                             ██   ██      ██        */
/*                                                     ███████  █████         */
/*   By: maroy <maroy@student.42.qc>                        ██ ██             */
/*                                                          ██ ███████.qc     */
/*   Created: 2023/07/31 15:20:11 by maroy                                    */
/*   Updated: 2023/10/04 17:20:54 by maroy            >(.)__ <(.)__ =(.)__    */
/*                                                     (___/  (___/  (___/    */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

uint8_t	env_builtin(t_data *data)
{
	int	i;

	i = -1;
	g_global->exit_status = EXIT_SUCCESS;
	i = -1;
	while (data->state->env_[++i] != NULL)
		ft_putendl_fd(data->state->env_[i], STDOUT_FILENO);
	return (OK);
}
