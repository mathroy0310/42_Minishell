/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maroy <maroy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/01 16:38:29 by maroy             #+#    #+#             */
/*   Updated: 2023/09/01 16:46:07 by maroy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

#include <stdbool.h>

void	print_sorted_env(char **sorted_env)
{
	int		i;
	int		j;
	bool	equ_sign;

	i = -1;
	while (sorted_env[++i])
	{
		j = 0;
		equ_sign = false;
		ft_putstr_fd("declare -x ", 1);
		while (sorted_env[i][j])
		{
			ft_putchar_fd(sorted_env[i][j], 1);
			if (sorted_env[i][j] == '=' && equ_sign)
			{
				ft_putchar_fd('"', 1);
				equ_sign = true;
			}
			j++;
		}
		if (equ_sign == true)
			ft_putendl_fd("\"", 1);
		else
			ft_putchar_fd('\n', 1);
	}
}

int	env_count(void)
{
	int	i;

	i = 0;
	while (g_global->env_var[i])
		i++;
	return (i);
}

char	**dup_env(void)
{
	char	**dup;
	int		i;

	i = env_count();
	dup = (char **)malloc(sizeof(char *) * (i + 1));
	if (!dup)
		return (NULL);
	dup[i] = 0;
	i--;
	while (i != -1)
	{
		dup[i] = g_global->env_var[i];
		i--;
	}
	return (dup);
}

void	sort_and_print(void)
{
	char	**dup;
	char	*tmp;
	int		i;
	int		j;

	dup = dup_env();
	i = 0;
	while (dup[i])
	{
		j = i + 1;
		while (dup[j])
		{
			if (ft_strcmp(dup[i], dup[j]) > 0)
			{
				tmp = dup[i];
				dup[i] = dup[j];
				dup[j] = tmp;
			}
			j++;
		}
		i++;
	}
	print_sorted_env(dup);
	free (dup);
}