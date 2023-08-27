/* ************************************************************************** */
/*                                                                            */
/*                                                     ██   ██ ██████         */
/*   file.c                                            ██   ██      ██        */
/*                                                     ███████  █████         */
/*   By: maroy <maroy@student.42.qc>                        ██ ██             */
/*                                                          ██ ███████.qc     */
/*   Created: 2023/07/14 21:56:43 by maroy                                    */
/*   Updated: 2023/08/27 13:25:55 by maroy            >(.)__ <(.)__ =(.)__    */
/*                                                     (___/  (___/  (___/    */
/* ************************************************************************** */

#include "../inc/minishell.h"

int8_t	handle_file(char *filename, int open_flag)
{
	int	fd;

	fd = open(filename, open_flag, 0644);
	if (fd == -1)
	{
		print_arg_error("no such file or directory: ", filename);
		return (EXIT_FAILURE);
	}
	return (fd);
}
