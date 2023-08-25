/* ************************************************************************** */
/*                                                                            */
/*                                                     ██   ██ ██████         */
/*   valid.c                                           ██   ██      ██        */
/*                                                     ███████  █████         */
/*   By: maroy <maroy@student.42.qc>                        ██ ██             */
/*                                                          ██ ███████.qc     */
/*   Created: 2023/07/14 21:56:43 by maroy                                    */
/*   Updated: 2023/08/24 15:51:49 by maroy            >(.)__ <(.)__ =(.)__    */
/*                                                     (___/  (___/  (___/    */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int8_t	check_redir(t_minishell *minishell, const char *buff)
{
	int	nb_redir;

	nb_redir = 0;
	while (buff[nb_redir] == '>')
	{
		nb_redir++;
		if (nb_redir > 2)
        {
            minishell->exit_status = 127;
			return (print_msg_error("syntax error near unexpected token `>\'"));
        }
	}
	return (EXIT_SUCCESS);
}

static int8_t	check_here(t_minishell *minishell, const char *buff)
{
	int	nb_here;

	nb_here = 0;
	while (buff[nb_here] == '<')
	{
		nb_here++;
		if (nb_here > 2)
        {
            minishell->exit_status = 127;
			return (print_msg_error("syntax error near unexpected token `<\'"));
        }
	}
	return (EXIT_SUCCESS);
}

static int8_t	check_pipes(t_minishell *minishell, const char *buff)
{
	int	nb_pipes;

	nb_pipes = 0;
	while (buff[nb_pipes] == '|')
	{
		nb_pipes++;
		if (nb_pipes > 1)
        {
            minishell->exit_status = 127;
			return (print_msg_error("syntax error near unexpected token `|\'"));
        }
	}
	return (EXIT_SUCCESS);
}

int8_t	using_valid_characters(char *buff, t_minishell *minishell)
{
	int	i;

	i = -1;
	if (buff == NULL)
		return (EXIT_FAILURE);
	while (buff[++i] != '\0')
	{
		if (buff[i] == '\'' && ft_strchr(&buff[i + 1], '\''))
			while (buff[++i] != '\'')
				;
		else if (buff[i] == '\"' && ft_strchr(&buff[i + 1], '\"'))
			while (buff[++i] != '\"')
				;
		if (check_redir(minishell, &buff[i]) || check_pipes(minishell, &buff[i])
			|| check_here(minishell, &buff[i]))
			return (EXIT_FAILURE);
		if (buff[i] == ';' || buff[i] == '\\' || buff[i] == '&')
			return (print_token_error(buff[i]));
	}
	return (EXIT_SUCCESS);
}
