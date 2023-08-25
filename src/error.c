/* ************************************************************************** */
/*                                                                            */
/*                                                     ██   ██ ██████         */
/*   error.c                                           ██   ██      ██        */
/*                                                     ███████  █████         */
/*   By: maroy <maroy@student.42.qc>                        ██ ██             */
/*                                                          ██ ███████.qc     */
/*   Created: 2023/07/31 17:43:00 by maroy                                    */
/*   Updated: 2023/08/24 18:36:23 by maroy            >(.)__ <(.)__ =(.)__    */
/*                                                     (___/  (___/  (___/    */
/* ************************************************************************** */

#include "../inc/minishell.h"

// on garde le format print_<type erreur>_error

int8_t	print_msg_error(char *msg)
{
    ft_putstr_fd(RED, STDERR_FILENO);
	ft_putstr_fd(PROMPT_ERROR, STDERR_FILENO);
	ft_putendl_fd(msg, STDERR_FILENO);
    ft_putstr_fd(DEFAULT, STDERR_FILENO);
    return (EXIT_FAILURE);
}

int8_t	print_token_error(char c)
{   
    ft_putstr_fd(RED, STDERR_FILENO);
	ft_putstr_fd(PROMPT_ERROR, STDERR_FILENO);
    ft_putchar_fd('`', STDERR_FILENO);
	ft_putchar_fd(c, STDERR_FILENO);
	ft_putendl_fd("' is not a valid token", STDERR_FILENO);
    ft_putstr_fd(DEFAULT, STDERR_FILENO);
	return (EXIT_FAILURE);
}
