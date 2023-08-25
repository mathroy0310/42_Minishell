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

static void	replace_if_matches(char *origin, char match, char replacement)
{
	if (*origin == match)
		*origin = replacement;
}

static void	tokenize_internal_quotes(char *str, char qt_repr, char dbl_qt_repr)
{
	int		i;

	i = -1;
	while (str[++i])
	{
		if (str[i] == '\"' && ft_strchr(&str[i + 1], '\"'))
		{
			while (str[++i] != '\"')
				replace_if_matches(&str[i], '\'', dbl_qt_repr);
		}
		else if (str[i] == '\'' && ft_strchr(&str[i + 1], '\''))
		{
			while (str[++i] != '\'')
				replace_if_matches(&str[i], '\"', qt_repr);
		}
	}
}

void	recover_internal_quotes(char *str, char qt_repr, char dbl_qt_repr)
{
	int		i;

	i = -1;
	while (str[++i])
	{
		if (str[i] == '\"' && ft_strchr(&str[i + 1], '\"'))
		{
			while (str[++i] != '\"')
				replace_if_matches(&str[i], dbl_qt_repr, '\'');
		}
		else if (str[i] == '\'' && ft_strchr(&str[i + 1], '\''))
		{
			while (str[++i] != '\'')
				replace_if_matches(&str[i], qt_repr, '\"');
		}
	}
}

static int	odd_nbr_quote_tokens(t_minishell *minishell, char *str)
{
	int		i;
	int		single_quotes;
	int		double_quotes;

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
	minishell->s_quotes = single_quotes;
	minishell->d_quotes = double_quotes;
	return (single_quotes % 2 == 1 || double_quotes % 2 == 1);
}

int8_t	handle_tokens(char *str, t_minishell *minishell)
{
	int	i;
	int	n_tokens;

	tokenize_internal_quotes(str, SQ_DELIM_CHAR, DQ_DELIM_CHAR);
	if (odd_nbr_quote_tokens(minishell, str))
	{
		minishell->exit_status = 127;
		return (print_msg_error("syntax error unbalanced quotes"));
	}
	n_tokens = ft_count_words(str, " ") + 30;
	minishell->argv = (char **)ft_calloc(n_tokens + 1, sizeof(char *));
	parsing(str, minishell->argv);
	i = -1;
	while (minishell->argv[++i])
		recover_internal_quotes(minishell->argv[i], SQ_DELIM_CHAR, DQ_DELIM_CHAR);
	minishell->argc = i;
	return (EXIT_SUCCESS);
}
