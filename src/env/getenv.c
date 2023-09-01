/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getenv.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maroy <maroy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 16:14:52 by maroy             #+#    #+#             */
/*   Updated: 2023/09/01 14:43:29 by maroy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	dup_env_var(char **env)
{
	int	i;

	i = -1;
	g_global->env_var = (char **)malloc(sizeof(char *) * (ft_tablen(env) + 1));
	if (g_global->env_var == NULL)
		exit(EXIT_FAILURE);
	while (++i < ft_tablen(env))
		g_global->env_var[i] = ft_strdup(env[i]);
	g_global->env_var[i] = 0;
	return (OK);
}

char	**get_env_(char	**env_)
{
	char	**env;
	int		i;

	i = -1;
	env = (char **)malloc(sizeof(char *) * (ft_tablen(env_) + 1));
	if (env == NULL)
		exit(EXIT_FAILURE);
	while (++i < ft_tablen(env_))
		env[i] = ft_strdup(env_[i]);
	env[i] = 0;
	return (env);
}