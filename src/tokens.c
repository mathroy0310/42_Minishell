/* ************************************************************************** */
/*                                                                            */
/*                                                     ██   ██ ██████         */
/*   tokens.c                                          ██   ██      ██        */
/*                                                     ███████  █████         */
/*   By: maroy <maroy@student.42.qc>                        ██ ██             */
/*                                                          ██ ███████.qc     */
/*   Created: 2023/08/09 13:36:25 by maroy                                    */
/*   Updated: 2023/08/18 17:39:45 by maroy            >(.)__ <(.)__ =(.)__    */
/*                                                     (___/  (___/  (___/    */
/* ************************************************************************** */

#include "../inc/minishell.h"
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
	t_dlist	*tokens;
	t_dlist	*tmp;
	char	*tok;
	char	delim[2];

	delim[0] = DELIM_CHAR;
	delim[1] = '\0';
	tmp = NULL;
	tok = NULL;
	tokens = ft_malloc(sizeof(t_dlist));
	tokens->content = NULL;
	tokens->next = NULL;
	tokens->prev = NULL;
	tok = ft_strtok(buffer, delim);
	while (tok != NULL)
	{
		tmp = ft_malloc(sizeof(t_list));
		tmp->content = ft_strdup(tok);
		tmp->next = NULL;
		tokens->next = tmp;
		tokens = tmp;
		printf("DEBUG : token  %s\n", tokens->content);
		tok = ft_strtok(NULL, delim);
	}
	minishell->tokens = tokens;
	return (OK);
}

int8_t	init_token(t_minishell *minishell, char *buffer)
{
	int		i;
	char	*normalized_buffer;

	i = -1;
	normalized_buffer = normalize_redirection(buffer);
	while (normalized_buffer[++i])
	{
		normalized_buffer[i] = ft_tolower(normalized_buffer[i]);
		if (normalized_buffer[i] == '\'' && ft_strchr(&normalized_buffer[i + 1],
			'\''))
			while (normalized_buffer[++i] != '\'')
				;
		if (normalized_buffer[i] == '\"' && ft_strchr(&normalized_buffer[i + 1],
			'\"'))
			while (normalized_buffer[++i] != '\"')
				;
		if (normalized_buffer[i] == ' ' | normalized_buffer[i] == '\t')
			normalized_buffer[i] = DELIM_CHAR;
	}
	if (split_tokens(minishell, normalized_buffer) == KO)
		return (KO);
	return (OK);
}
