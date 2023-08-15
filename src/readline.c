/* ************************************************************************** */
/*                                                                            */
/*                                                     ██   ██ ██████         */
/*   readline.c                                        ██   ██      ██        */
/*                                                     ███████  █████         */
/*   By: maroy <maroy@student.42.qc>                        ██ ██             */
/*                                                          ██ ███████.qc     */
/*   Created: 2023/07/14 21:56:43 by maroy                                    */
/*   Updated: 2023/08/15 16:12:50 by maroy            >(.)__ <(.)__ =(.)__    */
/*                                                     (___/  (___/  (___/    */
/* ************************************************************************** */

#include "../inc/minishell.h"

static void	save_history(char *input)
{
	if (input && *input)
		add_history(input);
}

int8_t	take_input(char *buffer)
{
	char	*trimmed;
	char	*input;

	input = readline("minishell$ ");
	if (input == NULL)
	{
		ft_putstr_fd("exit", STDOUT_FILENO);
		free(input);
		return (EXIT_FAILURE);
	}
	trimmed = ft_strtrim(input, " ");
	ft_strlcpy(buffer, trimmed, ft_strlen(trimmed) + 1);
	free(input);
	free(trimmed);
	if (ft_strlen(buffer) == 0)
		return (EXIT_SUCCESS);
	if (ft_strlen(buffer) > 0)
	{
		save_history(buffer);
		return (EXIT_SUCCESS);
	}
	return (EXIT_FAILURE);
}
