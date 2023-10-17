/* ************************************************************************** */
/*                                                                            */
/*                                                     ██   ██ ██████         */
/*   export_utils.c                                    ██   ██      ██        */
/*                                                     ███████  █████         */
/*   By: maroy <maroy@student.42.qc>                        ██ ██             */
/*                                                          ██ ███████.qc     */
/*   Created: 2023/09/13 15:17:33 by maroy                                    */
/*   Updated: 2023/10/17 16:43:43 by maroy            >(.)__ <(.)__ =(.)__    */
/*                                                     (___/  (___/  (___/    */
/* ************************************************************************** */

#include "minishell.h"

static void	print_sorted_env(char **sorted_env)
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
}

void	modify_env(char *arg, char *key)
{
	int		i;
	char	*new_value;
	char	*tmp;

	i = find_env_var_index(key, g_global->env_var);
	if (i == -1)
		return ;
	else
	{
		new_value = ft_strdup(arg);
		tmp = g_global->env_var[i];
		g_global->env_var[i] = new_value;
		free(tmp);
	}
}

char	**dup_env(void)
{
	char		**dup;
	int			i;

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
