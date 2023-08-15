/* ************************************************************************** */
/*                                                                            */
/*                                                     ██   ██ ██████         */
/*   free.c                                            ██   ██      ██        */
/*                                                     ███████  █████         */
/*   By: maroy <maroy@student.42.qc>                        ██ ██             */
/*                                                          ██ ███████.qc     */
/*   Created: 2023/08/15 15:56:17 by maroy                                    */
/*   Updated: 2023/08/15 16:15:06 by maroy            >(.)__ <(.)__ =(.)__    */
/*                                                     (___/  (___/  (___/    */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	free_env(t_list *env)
{
	t_list	*tmp;

	while (env && env->next)
	{
		tmp = env;
		env = env->next;
		free(tmp->content);
		free(tmp);
	}
	free(env->content);
	free(env);
}
