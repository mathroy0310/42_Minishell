/* ************************************************************************** */
/*                                                                            */
/*                                                     ██   ██ ██████         */
/*   error.c                                           ██   ██      ██        */
/*                                                     ███████  █████         */
/*   By: maroy <maroy@student.42.qc>                        ██ ██             */
/*                                                          ██ ███████.qc     */
/*   Created: 2023/07/31 17:43:00 by maroy                                    */
/*   Updated: 2023/08/15 15:55:21 by maroy            >(.)__ <(.)__ =(.)__    */
/*                                                     (___/  (___/  (___/    */
/* ************************************************************************** */

#include "../inc/minishell.h"

// on garde le format print_<type erreur>_error

int8_t	print_msg_error(t_minishell *minishell, char *msg)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putendl_fd(msg, STDERR_FILENO);
	minishell->exit_status = 2;
	return (EXIT_FAILURE);
}

int8_t	print_token_error(t_minishell *minishell, char c)
{
	ft_putstr_fd("minishell: syntax error: `", STDERR_FILENO);
	ft_putchar_fd(c, STDERR_FILENO);
	ft_putendl_fd("` is not a valid token", STDERR_FILENO);
	minishell->exit_status = 127;
	return (EXIT_FAILURE);
}
