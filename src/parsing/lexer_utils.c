/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maroy <maroy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 20:40:58 by maroy             #+#    #+#             */
/*   Updated: 2023/09/19 23:57:14 by maroy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	valid_envar(char c)
{
	if (ft_isalnum(c) || c == '_' || c == '~')
		return (OK);
	return (KO);
}

static void	ft_freeptr(void *ptr)
{
	free(ptr);
	ptr = NULL;
}

int	get_str_by_char(char *str, char c)
{
	int i;

	i = -1;
	while (str[++i])
	{
		if (str[i] == c)
			return (i);
	}
	return (KO);
}

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
		start = get_str_by_char(g_global->env_var[i], '=');
		env_key = ft_substr(g_global->env_var[i], 0, start);
		if (!ft_strcmp(env_key, str))
		{
			temp = env_value;
			env_value = ft_substr(g_global->env_var[i], start + 1, ft_strlen(g_global->env_var[i]) - start);
			free(temp);
			ft_freeptr(env_key);
			break ;
		}
		ft_freeptr(env_key);
	}
	return (env_value);
}

char	*string_envar(t_lexer *lexer)
{
	char	*str;

	if (ft_isdigit(lexer->c))
	{
		readchar(lexer);
		str = ft_strdup("");
		while (lexer->c != EOF && !ft_strchr("|><\"\' $", lexer->c))
		{
			str = ft_strjoin_char(str, lexer->c);
			readchar(lexer);
		}
	}
	else
	{
		str = ft_strdup("$");
		while (lexer->c != EOF && !ft_strchr("|><\"\'$", lexer->c))
		{
			str = ft_strjoin_char(str, lexer->c);
			readchar(lexer);
		}
	}
	return (str);
}

char	*invalid_envar(t_lexer *lexer, int i)
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
		readchar(lexer);
		s = tokenize_text(lexer, str);
		free(str);
		return (s);
	}
	else
	{
		str = ft_strdup("a");
		str[0] = lexer->c;
		readchar(lexer);
		return (str);
	}
}

char	*envar_token(t_lexer *lexer)
{
	char *str;
	char *v;

	if (!lexer)
		return (NULL);
	if (peek_char(lexer) == '$' || peek_char(lexer) == '\"'
		|| peek_char(lexer) == '\'' || peek_char(lexer) == EOF)
		return (invalid_envar(lexer, 0));
	readchar(lexer);
	if (ft_isdigit(lexer->c) || lexer->c == '?' || !valid_envar(lexer->c))
		return (invalid_envar(lexer, 1));
	str = ft_strdup("");
	while (valid_envar(lexer->c) && lexer->c != EOF)
	{
		str = ft_strjoin_char(str, lexer->c);
		readchar(lexer);
	}
	v = ft_getenv(str);
	free(str);
	if (!v)
		return (NULL);
	return (v);
}
