/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maroy <maroy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 20:40:58 by maroy             #+#    #+#             */
/*   Updated: 2023/12/08 20:29:30 by maroy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_getenv(char *str)
{
	char	*env_value;
	char	*env_key;
	char	*temp;
	int		i;
	int		start;

	env_value = ft_strdup("");
	i = -1;
	while (g_global->env_var[++i])
	{
		start = get_str_from_char(g_global->env_var[i], '=', TRUE);
		env_key = ft_substr(g_global->env_var[i], 0, start);
		if (!ft_strcmp(env_key, str))
		{
			temp = env_value;
			env_value = ft_substr(g_global->env_var[i], start + 1,
					ft_strlen(g_global->env_var[i]) - start);
			ft_free(temp);
			ft_free(env_key);
			break ;
		}
		ft_free(env_key);
	}
	return (env_value);
}

static char	*string_envar(t_lexer *lexer)
{
	char	*str;

	if (ft_isdigit(lexer->c))
	{
		read_single_char(lexer);
		str = ft_strdup("");
		while (lexer->c != EOF && !ft_strchr("|><\"\' $", lexer->c))
		{
			str = ft_strjoin_char(str, lexer->c);
			read_single_char(lexer);
		}
	}
	else
	{
		str = ft_strdup("$");
		while (lexer->c != EOF && !ft_strchr("|><\"\'$", lexer->c))
		{
			str = ft_strjoin_char(str, lexer->c);
			read_single_char(lexer);
		}
	}
	return (str);
}

static char	*invalid_envar(t_lexer *lexer, int i)
{
	char	*str;
	char	*s;

	if (i == 1)
	{
		if (lexer->c == '0')
			str = ft_strdup(PROMPT);
		else if (lexer->c == '?')
			str = ft_itoa(g_global->exit_status);
		else
			return (string_envar(lexer));
		read_single_char(lexer);
		s = tokenize_text(lexer, str);
		free(str);
		return (s);
	}
	else
	{
		str = ft_strdup("a");
		str[0] = lexer->c;
		read_single_char(lexer);
		return (str);
	}
}

static t_bool	is_tilde(char *str)
{
	if (!ft_strcmp(str, "~") || !ft_strcmp(str, "~/"))
		return (TRUE);
	return (FALSE);
}

char	*envar_token(t_lexer *lexer)
{
	char	*str;
	char	*v;

	if (!lexer)
		return (NULL);
	if (peek_char(lexer) == '$' || peek_char(lexer) == '\"'
		|| peek_char(lexer) == '\'' || peek_char(lexer) == EOF)
		return (invalid_envar(lexer, 0));
	read_single_char(lexer);
	if (ft_isdigit(lexer->c) || lexer->c == '?' || !is_valid_envar(lexer->c))
		return (invalid_envar(lexer, 1));
	str = ft_strdup("");
	while (is_valid_envar(lexer->c) && lexer->c != EOF)
	{
		str = ft_strjoin_char(str, lexer->c);
		read_single_char(lexer);
	}
	if (is_tilde(str))
		return (ft_getenv("HOME"));
	v = ft_getenv(str);
	free(str);
	if (!v)
		return (NULL);
	return (v);
}
