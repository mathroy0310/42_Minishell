/* ************************************************************************** */
/*                                                                            */
/*                                                     ██   ██ ██████         */
/*   file.c                                            ██   ██      ██        */
/*                                                     ███████  █████         */
/*   By: maroy <maroy@student.42.qc>                        ██ ██             */
/*                                                          ██ ███████.qc     */
/*   Created: 2023/07/14 21:56:43 by maroy                                    */
/*   Updated: 2023/08/04 13:36:27 by maroy            >(.)__ <(.)__ =(.)__    */
/*                                                     (___/  (___/  (___/    */
/* ************************************************************************** */

#include "../inc/minishell.h"

int8_t read_file(char *filename)
{
    int fd;

    fd = open(filename, O_RDONLY, 0644);
    if (fd == -1)
    {
        print_msg_error(NULL, "minishell: no such file or directory: %s");
        return (EXIT_FAILURE);
    }
    dup2(fd, 0);
    close(fd);
    return(fd);
}