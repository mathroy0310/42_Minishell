/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maroy <maroy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 14:22:40 by maroy             #+#    #+#             */
/*   Updated: 2023/12/08 19:58:35 by maroy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_u8	is_valid_option(char *arg)
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
		ft_putstr(args[i]);
		i++;
		if (args[i] != NULL)
			ft_putstr(" ");
	}
}

t_u8	echo_builtin(char **args)
{
	int j;

	g_global->exit_status = EXIT_SUCCESS;
	if (args[1] == NULL)
		ft_putstr_nl(NULL);
	else
	{
		if (is_valid_option(args[1]) == 1)
			check_n_option(args);
		else
		{
			j = 1;
			while (args[j] != NULL)
			{
				ft_putstr(args[j]);
				if (args[j + 1] != NULL)
					ft_putstr(" ");
				j++;
			}
			ft_putstr_nl(NULL);
		}
	}
	return (OK);
}