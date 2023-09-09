/* ************************************************************************** */
/*                                                                            */
/*                                                     ██   ██ ██████         */
/*   env.c                                             ██   ██      ██        */
/*                                                     ███████  █████         */
/*   By: maroy <maroy@student.42.qc>                        ██ ██             */
/*                                                          ██ ███████.qc     */
/*   Created: 2023/07/31 15:20:11 by maroy                                    */
/*   Updated: 2023/09/09 19:19:59 by maroy            >(.)__ <(.)__ =(.)__    */
/*                                                     (___/  (___/  (___/    */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

uint8_t	env_builtin(char **args, t_data *data)
{
	int	i;

	i = -1;
	g_global->exit_status = 0;
	i = -1;
	while (data->state->env_[++i] != NULL)
		ft_putendl_fd(data->state->env_[i], STDOUT_FILENO);
	if (env)
		ft_free_tab(env);
	return (OK);
}
