/* ************************************************************************** */
/*                                                                            */
/*                                                     ██   ██ ██████         */
/*   handle_pipes.c                                    ██   ██      ██        */
/*                                                     ███████  █████         */
/*   By: maroy <maroy@student.42.qc>                        ██ ██             */
/*                                                          ██ ███████.qc     */
/*   Created: 2023/09/23 16:34:02 by maroy                                    */
/*   Updated: 2023/09/23 16:36:20 by maroy            >(.)__ <(.)__ =(.)__    */
/*                                                     (___/  (___/  (___/    */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int8_t execute_simple_pipe(t_cmd *cmd, t_data *data)
{
	(void)data;
	(void)cmd;
	printf("execute_simple_pipe\n");
	return (OK);
}