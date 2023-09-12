/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maroy <maroy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 14:22:40 by maroy             #+#    #+#             */
/*   Updated: 2023/09/11 14:33:17 by maroy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

static uint8_t	is_valid_option(char *arg)
{
	int	i;

	i = 1;
	if (arg[0] == '-')
	{
		while (arg[i] != '\0')
		{
			if (arg[i] != 'n')
				return (KO);
			i++;
		}
		return (OK);
	}
	return (KO);
}

static void	check_n_option(char **args)
{
	int	i;

	if (args[2] == NULL)
		return ;
	i = 2;
	while (is_valid_option(args[i]) == 1)
	{
		i++;
		if (args[i] == NULL)
			return ;
	}
	while (args[i] != NULL)
	{
		ft_putstr_fd(args[i], STDOUT_FILENO);
		i++;
		if (args[i] != NULL)
			ft_putstr_fd(" ", STDOUT_FILENO);
	}
}

uint8_t	echo_builtin(char **args)
{
	int	j;

	g_global->exit_status = 0;
	if (args[1] == NULL)
		ft_putstr_fd("\n", STDOUT_FILENO);
	else
	{
		if (is_valid_option(args[1]) == 1)
			check_n_option(args);
		else
		{
			j = 1;
			while (args[j] != NULL)
			{
				ft_putstr_fd(args[j], STDOUT_FILENO);
				if (args[j + 1] != NULL)
					ft_putstr_fd(" ", STDOUT_FILENO);
				j++;
			}
			ft_putstr_fd("\n", STDOUT_FILENO);
		}
	}
	return (OK);
}
