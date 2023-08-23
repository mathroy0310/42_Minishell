/* ************************************************************************** */
/*                                                                            */
/*                                                     ██   ██ ██████         */
/*   parser.c                                          ██   ██      ██        */
/*                                                     ███████  █████         */
/*   By: maroy <maroy@student.42.qc>                        ██ ██             */
/*                                                          ██ ███████.qc     */
/*   Created: 2023/08/23 16:35:22 by maroy                                    */
/*   Updated: 2023/08/23 17:06:43 by maroy            >(.)__ <(.)__ =(.)__    */
/*                                                     (___/  (___/  (___/    */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	parse_tokens(t_token *tokens)
{
	if (tokens->content[0] == '-')
		tokens->type = FLAG;
	else if (tokens->content[0] == '|')
		tokens->type = PIPE;
	else if (tokens->content[0] == '>' || tokens->content[0] == '<')
		tokens->type = REDIRECT;
	else if (tokens->content[0] == '\"' && tokens->content[1] == '$')
		tokens->type = ENV_VAR;
	else if (tokens->content[0] == '\'' || tokens->content[0] == '\"')
		tokens->type = QUOTED_STRING;
	else if (tokens->content[0] == '$')
		tokens->type = ENV_VAR;
	else
		tokens->type = CMD;
}

int8_t	case_dollar_sign(t_minishell *minishell, t_token *tokens)
{
	char	*trimmed_content;
	int		i;

	i = -1;
	if (tokens->type == ENV_VAR)
	{
		trimmed_content = ft_strtrim(tokens->content, "$");
		while (trimmed_content[++i])
			trimmed_content[i] = ft_toupper(trimmed_content[i]);
		if (trimmed_content[0] == '?')
			tokens->content = ft_itoa(minishell->exit_status);
		else
			tokens->content = get_env_content(trimmed_content, minishell->env);
	}
	return (OK);
}

int8_t	case_quoted_string(t_minishell *minishell, t_token *tokens)
{
	char	*trimmed_content;

	(void)minishell;
	if (ft_strchr(tokens->content, '$') == NULL)
	{
		if (tokens->type == QUOTED_STRING)
		{
			trimmed_content = ft_strtrim(tokens->content, "\'\"");
			tokens->content = trimmed_content;
		}
	}
	return (OK);
}
