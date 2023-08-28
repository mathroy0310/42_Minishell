/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maroy <maroy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 21:56:43 by maroy             #+#    #+#             */
/*   Updated: 2023/08/28 15:02:31 by maroy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	handle_status(t_minishell *minishell, int i)
{
	if (minishell->argv[i][1] == '?'
		&& minishell->argv[i][2] == '\0')
	{
		free(minishell->argv[i]);
		minishell->argv[i] = ft_itoa(minishell->exit_status);
		return (1);
	}
	return (0);
}

int	handle_quotes(t_minishell *minishell, char *arg, int i)
{
	char	*token;

	token = ft_strchr(minishell->argv[i], *arg);
	if (token != NULL)
	{
		while (token != NULL)
		{
			ft_memmove(token, token + 1, ft_strlen(token));
			token = ft_strchr(minishell->argv[i], *arg);
		}
		return (1);
	}
	return (0);
}

void	handle_dollar_sign(t_minishell *minishell, char *tmp, int i)
{
	size_t	len;
	char	*token;

	len = ft_strlen(minishell->argv[i]);
	token = ft_strchr(minishell->argv[i], '$');
	if (token != NULL)
	{
		if (handle_status(minishell, i))
			return ;
		tmp = getenv_value(minishell->env, ++token);
		if (tmp)
		{
			free(minishell->argv[i]);
			minishell->argv[i] = ft_strdup(tmp);
		}
		else if (len == 1)
			return ;
		else
		{
			free(minishell->argv[i]);
			minishell->argv[i] = ft_strdup("");
		}
	}
}

void	handle_home(t_minishell *minishell, char *tmp, int i)
{
	char	*sign_start;
	char	*tmp_arg;

	if (ft_strchr(minishell->argv[i], '~') != NULL)
	{
		tmp_arg = ft_strdup(minishell->argv[i]);
		sign_start = ft_strchr(tmp_arg, '~');
		tmp = getenv_value(minishell->env, "HOME");
		free(minishell->argv[i]);
		if (++sign_start != NULL)
			minishell->argv[i] = ft_strjoin(tmp, sign_start);
		else
			minishell->argv[i] = ft_strdup(tmp);
		free(tmp_arg);
	}
}

void	expand_args(t_minishell *minishell)
{
	int		i;
	char	*tmp;

	i = -1;
	tmp = NULL;
	while (minishell->argv[++i])
	{
		if (minishell->s_quotes >= 2 && handle_quotes(minishell, "\'", i))
			continue ;
		if (minishell->d_quotes >= 2)
			handle_quotes(minishell, "\"", i);
		if (!(ft_strncmp(minishell->argv[i], "$", 2) == 0))
			handle_dollar_sign(minishell, tmp, i);
		handle_home(minishell, tmp, i);
	}
	minishell->argc = i;
}