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

void	destroy_program(t_minishell *minishell)
{
	ft_lstclear(minishell->env, free);
	free(minishell);
}