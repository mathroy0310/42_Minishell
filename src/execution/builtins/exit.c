/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maroy <maroy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 17:53:21 by maroy             #+#    #+#             */
/*   Updated: 2024/01/02 00:09:53 by maroy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <limits.h>

t_bool	is_only_digit_and_sign(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (FALSE);
		i++;
	}
	return (TRUE);
}

t_u8	exit_builtin(char **args)
{
	g_global->has_exited = TRUE;
	ft_putstr_nl("exit");
	if (args[1] && is_only_digit_and_sign(args[1]) == TRUE)
	{
		if (args[2])
		{
			ft_putstr_err(FT_RED ERR_PROMPT "exit: too many arguments");
			ft_putstr_errnl(FT_COLOR_RESET);
			g_global->exit_status = 1;
			return (KO);
		}
		g_global->exit_status = ft_atoi(args[1]);
	}
	else if (args[1] && is_only_digit_and_sign(args[1]) == FALSE)
	{
		ft_putstr_err(FT_RED ERR_PROMPT "exit: ");
		ft_putstr_err(args[1]);
		ft_putstr_err(": numeric argument required");
		ft_putstr_errnl(FT_COLOR_RESET);
		g_global->exit_status = 2;
		return (KO);
	}
	else
		g_global->exit_status = EXIT_SUCCESS;
	return (OK);
}
