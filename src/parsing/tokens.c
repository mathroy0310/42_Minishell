/* ************************************************************************** */
/*                                                                            */
/*                                                     ██   ██ ██████         */
/*   tokens.c                                          ██   ██      ██        */
/*                                                     ███████  █████         */
/*   By: maroy <maroy@student.42.qc>                        ██ ██             */
/*                                                          ██ ███████.qc     */
/*   Created: 2023/08/09 13:36:25 by maroy                                    */
/*   Updated: 2023/08/23 16:42:55 by maroy            >(.)__ <(.)__ =(.)__    */
/*                                                     (___/  (___/  (___/    */
/* ************************************************************************** */

#include "../../inc/minishell.h"
#include <stdbool.h>

static int	count_redirections(char *input)
{
	int	total;

	total = 0;
	total += ft_count_char(input, '|');
	total += ft_count_char(input, '>');
	total += ft_count_char(input, '<');
	return (total);
}

char	*normalize_redirection(char *input)
{
	size_t	i;
	int		j;
	char	*modified;
	bool	inside_quotes;
	bool	inside_double_quotes;

	modified = (char *)ft_malloc((ft_strlen(input) + (count_redirections(input)
				* 2)) + 1);
	i = -1;
	j = 0;
	while (input[++i])
	{
		if (input[i] == '\'' && !inside_double_quotes)
			inside_quotes = !inside_quotes;
		if (input[i] == '\"' && !inside_quotes)
			inside_double_quotes = !inside_double_quotes;
		if ((!inside_quotes && !inside_double_quotes) && (input[i] == '|'
				|| input[i] == '<' || input[i] == '>'))
		{
			modified[j++] = DELIM_CHAR;
			modified[j++] = input[i];
			modified[j++] = DELIM_CHAR;
		}
		else
			modified[j++] = input[i];
	}
	modified[j] = '\0';
	return (modified);
}

int8_t	split_tokens(t_minishell *minishell, char *buffer)
{
	t_token	*tokens;
	t_token	*tmp;
	char	*tok;
	char	delim[2];

	delim[0] = DELIM_CHAR;
	delim[1] = '\0';
	tmp = NULL;
	tok = NULL;
	tokens = ft_malloc(sizeof(t_token));
	tokens->content = NULL;
	tokens->next = NULL;
	tokens->prev = NULL;
	tok = ft_strtok(buffer, delim);
	while (tok != NULL)
	{
		tmp = ft_malloc(sizeof(t_token));
		tmp->content = ft_strdup(tok);
		tmp->next = NULL;
		tokens->next = tmp;
		tokens = tmp;
		parse_tokens(tokens);
		if (case_quoted_string(minishell, tokens) == KO || case_dollar_sign(minishell, tokens) == KO)
			ft_putendl_fd("DEBUG : gros fail", 2);
        DEBUG_print_msg("token is", tokens->content);
		DEBUG_print_token_type(tokens);
		free(tmp->content);
		tok = ft_strtok(NULL, delim);
	}
	minishell->tokens = tokens;
	return (OK);
}

int8_t	init_token(t_minishell *minishell, char *buffer)
{
	int		i;
	char	*normal_buff;

	i = -1;
	normal_buff = normalize_redirection(buffer);
	while (normal_buff[++i])
	{
		normal_buff[i] = ft_tolower(normal_buff[i]);
		if (normal_buff[i] == '\'' && ft_strchr(&normal_buff[i + 1], '\''))
			while (normal_buff[++i] != '\'')
				;
		if (normal_buff[i] == '\"' && ft_strchr(&normal_buff[i + 1], '\"'))
			while (normal_buff[++i] != '\"')
				;
		if (normal_buff[i] == ' ' | normal_buff[i] == '\t')
			normal_buff[i] = DELIM_CHAR;
	}
	if (split_tokens(minishell, normal_buff) == KO)
		return (KO);
	return (OK);
}
