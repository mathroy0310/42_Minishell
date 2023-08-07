/* ************************************************************************** */
/*                                                                            */
/*                                                     ██   ██ ██████         */
/*   valid.c                                           ██   ██      ██        */
/*                                                     ███████  █████         */
/*   By: maroy <maroy@student.42.qc>                        ██ ██             */
/*                                                          ██ ███████.qc     */
/*   Created: 2023/07/14 21:56:43 by maroy                                    */
/*   Updated: 2023/08/04 13:36:27 by maroy            >(.)__ <(.)__ =(.)__    */
/*                                                     (___/  (___/  (___/    */
/* ************************************************************************** */

#include "../inc/minishell.h"

static int	check_redir(t_minishell *minishell, const char *buff)
{
	int	nb_redir;

	nb_redir = 0;
	while (buff[nb_redir] == '>')
	{
		nb_redir++;
		if (nb_redir > 2)
			return (print_msg_error(minishell, "minishell: syntax error near unexpected token `>\'"));
	}
	return (0);
}

static int	check_pipes(t_minishell *minishell, const char *buff)
{
	int		nb_pipes;

	nb_pipes = 0;
	while (buff[nb_pipes] == '|')
	{
		nb_pipes++;
		if (nb_pipes > 1)
			return (print_msg_error(minishell, "minishell: syntax error near unexpected token `|\'"));
	}
	return (0);
}

int	using_valid_characters(char *buff, t_minishell *minishell)
{
	int		i;

	i = -1;
	if (buff == NULL)
		return (1);
	while (buff[++i] != '\0')
	{
		if (buff[i] == '\'' && ft_strchr(&buff[i + 1], '\''))
			while (buff[++i] != '\'')
				;
		else if (buff[i] == '\"' && ft_strchr(&buff[i + 1], '\"'))
			while (buff[++i] != '\"')
				;
		if (check_redir(minishell, &buff[i]) || check_pipes(minishell, &buff[i]))
			return (1);
		if (buff[i] == ';' || buff[i] == '\\' || buff[i] == '&')
			return (print_token_error(minishell, buff[i]));
	}
	return (0);
}