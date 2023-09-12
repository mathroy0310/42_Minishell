/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maroy <maroy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 17:53:21 by maroy             #+#    #+#             */
/*   Updated: 2023/09/12 18:08:58 by maroy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

#include <limits.h>

void	error_exit(char *arg)
{
	ft_putendl_fd("exit", STDOUT_FILENO);
	ft_putstr_fd("minishell: exit: ", STDERR_FILENO);
	ft_putstr_fd(arg, STDERR_FILENO);
	ft_putendl_fd(": numeric argument required", STDERR_FILENO);
	exit (255);
}

long long	atoi_exit(const char *str)
{
	int					signe;
	unsigned long long	r;
	char				*error_tmp;

	error_tmp = (char *)str;
	signe = 1;
	r = 0;
	while (*str >= 9 && *str <= SPACE)
		str++;
	if (*str == '-')
	{
		signe = -1;
		str++;
	}
	else if (*str == '+')
		str++;
	while (*str >= '0' && *str <= '9')
	{
		r = r * 10 + *str - '0';
		if (r > LLONG_MAX)
			error_exit(error_tmp);
		str++;
	}
	ft_putendl_fd("exit", STDERR_FILENO);
	exit (r * signe);
}

void	exit_number(char *arg)
{
	int	i;

	i = 0;
	if (arg[i] != '\0')
	{
		while (arg[i])
		{
			if (arg[0] == '-' || arg[0] == '+')
				i++;
			if (arg[i] < '0' || arg[i] > '9' )
			{
				ft_putendl_fd("exit", STDOUT_FILENO);
				ft_putstr_fd("minishell: exit: ", STDERR_FILENO);
				ft_putstr_fd(arg, STDERR_FILENO);
				ft_putendl_fd(": numeric argument required", STDERR_FILENO);
				exit (255);
			}
			i++;
		}	
	}
	atoi_exit(arg);
}

int	check_for_num_arg(char *args)
{
	int	i;
	int	is_alpha;

	i = 0;
	is_alpha = 0;
	while (args[i])
	{
		if (args[0] == '-' || args[0] == '+')
			i++;
		if (args[i] < '0' || args[i] > '9')
			is_alpha = 1;
		i++;
	}
	if (!is_alpha)
	{
		ft_putendl_fd("exit", STDOUT_FILENO);
		ft_putendl_fd("minishell: exit: too many arguments", STDERR_FILENO);
		g_global->exit_status = 1;
	}
	else
		error_exit(args);
	return (EXIT_SUCCESS);
}

uint8_t	exit_builtin(char **args)
{
	char	*trim_arg;

	trim_arg = ft_strtrim(args[1], " ");
	if (ft_tablen(args) > 2)
		return (check_for_num_arg(trim_arg));
	else if (args[1])
	{
		if (!ft_strcmp(trim_arg, "-9223372036854775808"))
		{
			ft_putendl_fd("exit", STDOUT_FILENO);
			exit(EXIT_SUCCESS);
		}
		exit_number(trim_arg);
	}
	else
	{
		ft_putendl_fd("exit", STDOUT_FILENO);
		exit (g_global->exit_status);
	}
	return (OK);
}
