/* ************************************************************************** */
/*                                                                            */
/*                                                     ██   ██ ██████         */
/*   exit.c                                            ██   ██      ██        */
/*                                                     ███████  █████         */
/*   By: maroy <maroy@student.42.qc>                        ██ ██             */
/*                                                          ██ ███████.qc     */
/*   Created: 2023/09/12 17:53:21 by maroy                                    */
/*   Updated: 2023/10/28 18:29:31 by maroy            >(.)__ <(.)__ =(.)__    */
/*                                                     (___/  (___/  (___/    */
/* ************************************************************************** */

#include "minishell.h"
#include <limits.h>
#define ERR_EXIT "exit: too many arguments"

void	error_exit(char *arg)
{
	ft_putstr_nl("exit");
	ft_putstr(ANSI_COLOR_BRIGHT_RED ERR_PROMPT "exit: ");
	ft_putstr(arg);
	ft_putstr(": numeric argument required");
	ft_putstr_nl(ANSI_COLOR_RESET);
	exit(255);
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
	//ft_putstr_errnl("exit");
	exit(r * signe);
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
			if (arg[i] < '0' || arg[i] > '9')
			{
				ft_putstr_nl("exit");
				ft_putstr(ERR_PROMPT "exit: ");
				ft_putstr(arg);
				ft_putstr_nl(": numeric argument required");
				exit(255);
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
		ft_putstr_nl("exit");
		ft_putstr_err(ANSI_COLOR_BRIGHT_RED ERR_PROMPT ERR_EXIT);
		ft_putstr_errnl(ANSI_COLOR_RESET);
		g_global->exit_status = EXIT_FAILURE;
	}
	else
		error_exit(args);
	return (EXIT_SUCCESS);
}

t_u8	exit_builtin(char **args)
{
	char	*trim_arg;

	trim_arg = ft_strtrim(args[1], " ");
	if (ft_tablen(args) > 2)
		return (check_for_num_arg(trim_arg));
	else if (args[1])
	{
		if (!ft_strcmp(trim_arg, "-9223372036854775808"))
		{
			ft_putstr_nl("exit");
			exit(EXIT_SUCCESS);
		}
		exit_number(trim_arg);
	}
	else
	{
		ft_putstr_nl("exit");
		exit(g_global->exit_status);
	}
	return (OK);
}
