/* ************************************************************************** */
/*                                                                            */
/*                                                     ██   ██ ██████         */
/*   tokens.c                                          ██   ██      ██        */
/*                                                     ███████  █████         */
/*   By: maroy <maroy@student.42.qc>                        ██ ██             */
/*                                                          ██ ███████.qc     */
/*   Created: 2023/08/09 13:36:25 by maroy                                    */
/*   Updated: 2023/08/24 20:51:27 by maroy            >(.)__ <(.)__ =(.)__    */
/*                                                     (___/  (___/  (___/    */
/* ************************************************************************** */

#include "../../inc/minishell.h"
#include <stdbool.h>

// static int	count_redirections(char *input)
// {
// 	int	total;

// 	total = 0;
// 	total += ft_count_char(input, '|');
// 	total += ft_count_char(input, '>');
// 	total += ft_count_char(input, '<');
// 	return (total);
// }

// char	*normalize_redirection(char *input)
// {
// 	size_t	i;
// 	int		j;
// 	char	*modified;
// 	bool	inside_quotes;
// 	bool	inside_double_quotes;

// 	modified = (char *)ft_malloc((ft_strlen(input) + (count_redirections(input)
// 				* 2)) + 1);
// 	i = -1;
// 	j = 0;
// 	while (input[++i])
// 	{
// 		if (input[i] == '\'' && !inside_double_quotes)
// 			inside_quotes = !inside_quotes;
// 		if (input[i] == '\"' && !inside_quotes)
// 			inside_double_quotes = !inside_double_quotes;
// 		if ((!inside_quotes && !inside_double_quotes) && (input[i] == '|'
// 				|| input[i] == '<' || input[i] == '>'))
// 		{
// 			modified[j++] = DELIM_CHAR;
// 			modified[j++] = input[i];
// 			modified[j++] = DELIM_CHAR;
// 		}
// 		else
// 			modified[j++] = input[i];
// 	}
// 	modified[j] = '\0';
// 	return (modified);
// }

// int8_t	split_tokens(t_minishell *minishell, char *buffer)
// {
// 	t_token	*tokens;
// 	t_token	*tmp;
// 	char	*tok;
// 	char	delim[2];

// 	delim[0] = DELIM_CHAR;
// 	delim[1] = '\0';
// 	tmp = NULL;
// 	tok = NULL;
// 	tokens = ft_malloc(sizeof(t_token));
// 	tokens->content = NULL;
// 	tokens->next = NULL;
// 	tokens->prev = NULL;
// 	tok = ft_strtok(buffer, delim);
// 	while (tok != NULL)
// 	{
// 		tmp = ft_malloc(sizeof(t_token));
// 		tmp->content = ft_strdup(tok);
// 		tmp->next = NULL;
// 		tokens->next = tmp;
// 		tokens = tmp;
// 		parse_tokens(tokens);
// 		if (case_quoted_string(minishell, tokens) == KO || case_dollar_sign(minishell, tokens) == KO)
// 			ft_putendl_fd("DEBUG : gros fail", 2);
//         DEBUG_print_msg("token is", tokens->content);
// 		DEBUG_print_token_type(tokens);
// 		free(tmp->content);
// 		tok = ft_strtok(NULL, delim);
// 	}
// 	minishell->tokens = tokens;
// 	return (OK);
// }

static void replace_if_matches(char *src, char match, char replace)
{
    if (*src == match)
        *src = replace;
}

static void internal_quotes(char *str, char SQ_D, char DQ_D)
{
    int i;
    
    i = -1;
    while (str[++i])
    {
        if (str[i] == '\"' && ft_strchr(&str[i + 1], '\"'))
        {
            while (str[++i] != '\"')
                replace_if_matches(&str[i], ' ', DQ_D);
        }
        if (str[i] == '\'' && ft_strchr(&str[i + 1], '\''))
        {
            while (str[++i] != '\'')
                replace_if_matches(&str[i], ' ', SQ_D);
        }
    }
}

static void recover_internal_quotes(char *str, char SQ_D, char DQ_D)
{
    int i;
    
    i = -1;
    while (str[++i])
    {
        if (str[i] == '\"' && ft_strchr(&str[i + 1], '\"'))
        {
            while (str[++i] != '\"')
                replace_if_matches(&str[i],  DQ_D , ' ');
        }
        if (str[i] == '\'' && ft_strchr(&str[i + 1], '\''))
        {
            while (str[++i] != '\'')
                replace_if_matches(&str[i],  SQ_D , ' ' );
        }
    }
}

static int odd_nbr_quotes(t_minishell *minishell, char *str)
{
    int i;
    int single_quotes;
    int double_quotes;
    
    (void)minishell;
    i = -1;
    single_quotes = 0;
    double_quotes = 0;
    while (str[++i])
    {
        if (str[i] == '\'')
            single_quotes++;
        if (str[i] == '\"')
            double_quotes++;          
    }
    // DEBUG_print_msg("single quotes", ft_itoa(single_quotes));
    // DEBUG_print_msg("double quotes", ft_itoa(double_quotes));
    minishell->cmd->s_quotes = single_quotes;
    minishell->cmd->d_quotes = double_quotes;
    // DEBUG_print_msg("minishell->cmd->s_quotes is : ", ft_itoa(minishell->cmd->s_quotes));
    // DEBUG_print_msg("minishell->cmd->d_quotes is : ", ft_itoa(minishell->cmd->d_quotes));
    return (single_quotes % 2 != 0 || double_quotes % 2 != 0);
}

int8_t	init_token(t_minishell *minishell, char *buffer)
{
    int i;
    int nbr_tokens;

    
    internal_quotes(buffer, SQ_DELIM_CHAR, DQ_DELIM_CHAR);
    //DEBUG_print_msg("buffer is", buffer);
    if (odd_nbr_quotes(minishell, buffer))
    {
        minishell->exit_status = 127;
        return (print_msg_error("odd number of quotes"));
    }
    nbr_tokens = ft_count_words(buffer, " ") + 30;
    minishell->argv = (char **)ft_calloc(nbr_tokens + 1, sizeof(char *));
    parse(buffer, minishell->argv);
    DEBUG_print_msg("nbr_tokens is", ft_itoa(nbr_tokens));
    DEBUG_print_msg("buffer is", buffer);
    DEBUG_print_msg("minishell->argv[0] is", minishell->argv[0]);
    DEBUG_print_msg("minishell->argv[1] is", minishell->argv[1]);
    DEBUG_print_msg("minishell->argv[2] is", minishell->argv[2]);
    DEBUG_print_tab(minishell->argv);
    i = -1;
    while (minishell->argv[++i])
        recover_internal_quotes(minishell->argv[i], SQ_DELIM_CHAR, DQ_DELIM_CHAR);
    minishell->argc = i;
    return (EXIT_SUCCESS);
}
